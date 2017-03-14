#include "interactivecommand.h"

#include <QMetaMethod>
#include <QTextStream>

namespace Engnr {
namespace InteractiveShell {

const char *CommandPostfix = "Command";
const int CommandPostfixSize = sizeof(CommandPostfix) - 1;
const char *HelpPostfix = "Help";
const int ShiftSpaces = 4;
const int MaxHelpFieldSize = 15;

void muteMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    QByteArray localMsg = message.toLocal8Bit();
    if (type == QtFatalMsg)
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
    if (type == QtCriticalMsg)
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
}

InteractiveCommand::InteractiveCommand(QObject *parent) :
    QObject(parent),
    m_muted(false),
    m_oldMessageHandler(0)
{
}

void InteractiveCommand::addCommand(InteractiveCommand *command)
{
    command->setParent(this);
    m_commands << command;
}

void InteractiveCommand::removeCommand(InteractiveCommand *command)
{
    if (m_commands.removeOne(command))
        command->deleteLater();
}

bool InteractiveCommand::parse(QStringList args)
{
    if (args.isEmpty())
        return false;

    QString arg = args.takeFirst();
    if (runMethod(arg, args))
        return true;

    if (runCommand(arg, args))
        return true;

    return false;
}

QString InteractiveCommand::name() const
{
    QString className = metaObject()->className();
    return className.toLower();
}

void InteractiveCommand::run()
{
    helpCommand();
}

QString InteractiveCommand::description() const
{
    return QString();
}

void InteractiveCommand::helpCommand()
{
    const QMetaObject *mo = metaObject();

    int fieldSize = 0;
    QList<QPair<QString, QString>> helpMessages;

    for (int i = 0; i < mo->methodCount(); i++) {
        const QMetaMethod method = mo->method(i);
        QByteArray methodName = method.name();

        if (methodName.endsWith(CommandPostfix)) {
            methodName.chop(CommandPostfixSize);

            QPair<QString, QString> helpMessage;
            helpMessage.first = methodName.toLower();

            QList<QByteArray> parameters = method.parameterNames();
            for (const QByteArray &parameter : parameters)
                helpMessage.first += " " + parameter.toUpper();

            fieldSize = qMax(fieldSize, helpMessage.first.size());

            QByteArray signature = methodName + HelpPostfix + "()";
            int index = mo->indexOfMethod(signature);
            if (index > 0) {
                QMetaMethod helpMethod = mo->method(index);
                QString help;
                helpMethod.invoke(this, Qt::DirectConnection, Q_RETURN_ARG(QString, help));
                helpMessage.second = help;
            }

            helpMessages << helpMessage;
        }
    }

    for (InteractiveCommand *command : m_commands) {
        QPair<QString, QString> helpMessage;
        helpMessage.first = command->name();
        helpMessage.second = command->description();
        helpMessages << helpMessage;
        fieldSize = qMax(fieldSize, helpMessage.first.size());
    }

    for (const auto helpMessage : helpMessages) {
        say() << QString(' ').repeated(ShiftSpaces)
              << helpMessage.first.leftJustified(fieldSize)
              << QString(' ').repeated(fieldSize > MaxHelpFieldSize ? 0 : ShiftSpaces)
              << helpMessage.second;
    }
}

QString InteractiveCommand::helpHelp()
{
    return QString("List available commands");
}

void InteractiveCommand::print(const QString &message, int spaces) const
{
    QTextStream out(stdout);
    QString space(" ");
    out << space.repeated(spaces) << message;
}

void InteractiveCommand::printLine(const QString &message, int spaces) const
{
    QTextStream out(stdout);
    QString space(" ");
    out << space.repeated(spaces) << message << "\n";
}

QDebug InteractiveCommand::say() const
{
    return QDebug(QtInfoMsg).noquote();
}

void InteractiveCommand::say(const QString &message) const
{
    QDebug debug(QtInfoMsg);
    debug << message;
}

void InteractiveCommand::say(const QString &message, const Color &color) const
{
    say().nospace() << color << message << Color::clear();
}

void InteractiveCommand::say(const QString &message, const Colors &colors) const
{
    say().nospace() << colors << message << Color::clear();
}

QString InteractiveCommand::ask(const QString &question, int spaces)
{
    printLine(question, spaces);
    QTextStream in(stdin);
    return in.readLine();
}

bool InteractiveCommand::yes(const QString &statement)
{
    forever {
        printLine(statement);
        QString answer = ask(QString("yes/no?"), ShiftSpaces);
        if (answer == "yes" || answer == "y")
            return true;
        else if (answer == "no" || answer == "n")
            return false;
        else
            printLine("Please answer yes or no");
    };
}

bool InteractiveCommand::no(const QString &statement)
{
    return !yes(statement);
}

void InteractiveCommand::mute()
{
    m_muted = true;
    m_oldMessageHandler = qInstallMessageHandler(muteMessageHandler);
}

void InteractiveCommand::unmute()
{
    m_muted = false;
    if (m_oldMessageHandler)
        qInstallMessageHandler(m_oldMessageHandler);
}

bool InteractiveCommand::isMuted() const
{
    return m_muted;
}

void InteractiveCommand::setColor(const Color &color)
{
    print(color.color());
}

void InteractiveCommand::setColors(const Colors &colors)
{
    for (const Color &color : colors)
        print(color.color());
}

void InteractiveCommand::clearColor()
{
    print(Color::clear().color());
}

bool InteractiveCommand::runMethod(const QString &commandString, const QStringList &args)
{
    for (int i = 0; i < metaObject()->methodCount(); i++) {
        QMetaMethod method = metaObject()->method(i);
        if (checkMethodName(method, commandString)
                && invokeMethod(method, args)) {
            return true;
        }
    }

    return false;
}

bool InteractiveCommand::runCommand(const QString &commandString, const QStringList &args)
{
    for (InteractiveCommand *command : m_commands) {
        if (command->name() == commandString) {
            if (!command->parse(args))
                command->run();
            return true;
        }
    }

    return false;
}

bool InteractiveCommand::invokeMethod(const QMetaMethod &method, const QStringList &args)
{
    if (!checkArguments(method, args))
        return false;

    switch (method.parameterCount()) {
    case 0:
        return method.invoke(this, Qt::DirectConnection);
    case 1:
        return method.invoke(this, Qt::DirectConnection,
                             Q_ARG(QVariant, args.at(0)));
    case 2:
        return method.invoke(this, Qt::DirectConnection,
                             Q_ARG(QVariant, args.at(0)),
                             Q_ARG(QVariant, args.at(1)));
    case 3:
        return method.invoke(this, Qt::DirectConnection,
                             Q_ARG(QVariant, args.at(0)),
                             Q_ARG(QVariant, args.at(1)),
                             Q_ARG(QVariant, args.at(2)));
    }

    return false;
}

bool InteractiveCommand::checkMethodName(const QMetaMethod &method, const QString &command)
{
    if (method.access() != QMetaMethod::Public
            || method.methodType() != QMetaMethod::Slot)
        return false;


    QByteArray methodName = method.name();
    int offset = methodName.size() - CommandPostfixSize;

    if (methodName.mid(offset) != CommandPostfix)
        return false;

    QByteArray methodCommand = methodName.left(offset);
    return methodCommand.toLower() == command;
}

bool InteractiveCommand::checkArguments(const QMetaMethod &method, const QStringList &args)
{
    if (method.parameterCount() != args.size())
        return false;

    for (int i = 0; i < method.parameterCount(); i++) {
        if (method.parameterType(i) != QMetaType::QVariant)
            return false;
    }

    return true;
}

} // namespace InteractiveShell
} // namespace Engnr

