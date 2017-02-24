#include "interactivecommand.h"

#include <QMetaMethod>

namespace Engnr {
namespace InteractiveShell {

const char *CommandPostfix = "Command";

InteractiveCommand::InteractiveCommand(QObject *parent) :
    QObject(parent)
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
        return true;

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
            if (command->name() == arg && command->parse(args))
                return true;
        }
    }

    return false;
}

QString InteractiveCommand::name() const
{
    QString className = metaObject()->className();
    return className.toLower();
}

void InteractiveCommand::print(const QString &message)
{
    QTextStream out(stdout);
    out << message;
}

void InteractiveCommand::printLine(const QString &message)
{
    QTextStream out(stdout);
    out << message << "\n";
}

} // namespace InteractiveShell
} // namespace Engnr

