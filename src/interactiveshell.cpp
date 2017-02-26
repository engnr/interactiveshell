#include "interactiveshell.h"

#include "interactivecommand.h"
#include <QDebug>

namespace Engnr {
namespace InteractiveShell {

InteractiveShell::InteractiveShell(QObject *parent) :
    AbstractInteractiveShell(parent),
    m_rootCommand(0)
{
}

void InteractiveShell::run()
{
    prompt();
}

void InteractiveShell::setRootCommand(InteractiveCommand *rootCommand)
{
    if (m_rootCommand)
        m_rootCommand->deleteLater();

    m_rootCommand = rootCommand;
}

void InteractiveShell::parse(const QByteArray &command)
{
    if (command.isEmpty())
        return;

    if (m_rootCommand) {
        QStringList args = QString(command).split(" ");
        if (!m_rootCommand->parse(args))
            qDebug() << "command not found";
    }
}

} // namespace InteractiveShell
} // namespace Engnr

