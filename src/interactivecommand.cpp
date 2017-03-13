#include "interactivecommand.h"

#include <QMetaMethod>
#include <QTextStream>

namespace Engnr {
namespace InteractiveShell {

const char *CommandPostfix = "Command";
const int CommandPostfixSize = sizeof(CommandPostfix) - 1;
const char *HelpPostfix = "Help";
const int ShiftSpaces = 4;

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
    QString commandName = arg + CommandPostfix;
    QByteArray methodName = commandName.toLatin1() + "()";
    QByteArray signature = QMetaObject::normalizedSignature(methodName.constData());
    int index = metaObject()->indexOfMethod(signature);

    if (index > 0) {
        QMetaMethod method = metaObject()->method(index);
        if (method.access() == QMetaMethod::Public
                && method.methodType() == QMetaMethod::Slot) {
            return method.invoke(this, Qt::DirectConnection);
        }
    } else {
        for (InteractiveCommand *command : m_commands) {
            if (command->name() == arg) {
                if (!command->parse(args))
                    command->run();
                return true;
            }
        }
    }

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
    for (int i = 0; i < mo->methodCount(); i++) {
        const QMetaMethod method = mo->method(i);
        QByteArray methodName = method.name();
        if (methodName.endsWith(CommandPostfix)) {
            methodName.chop(CommandPostfixSize);
            print(methodName + " - ", ShiftSpaces);

            QByteArray signature = methodName + HelpPostfix + "()";
            int index = mo->indexOfMethod(signature);
            if (index > 0) {
                QMetaMethod helpMethod = mo->method(index);
                QString help;
                helpMethod.invoke(this, Qt::DirectConnection, Q_RETURN_ARG(QString, help));
                printLine(help);
            }
        }
    }

    for (InteractiveCommand *command : m_commands)
        printLine(QString("%1 - %2")
                  .arg(command->name())
                   .arg(command->description()),
                  ShiftSpaces);
}

QString InteractiveCommand::helpHelp()
{
    return QString("List available commands");
}

void InteractiveCommand::print(const QString &message, int spaces)
{
    QTextStream out(stdout);
    QString space(" ");
    out << space.repeated(spaces) << message;
}

void InteractiveCommand::printLine(const QString &message, int spaces)
{
    QTextStream out(stdout);
    QString space(" ");
    out << space.repeated(spaces) << message << "\n";
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

} // namespace InteractiveShell
} // namespace Engnr

