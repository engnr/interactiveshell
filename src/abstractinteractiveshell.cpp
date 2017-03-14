#include "abstractinteractiveshell.h"

#include "interactivecommand.h"
#include <QDebug>

namespace Engnr {
namespace InteractiveShell {

AbstractInteractiveShell::AbstractInteractiveShell(QObject *parent) :
    QObject(parent),
    m_promptPrefix(">>> "),
    m_rootCommand(0)
{
}

void AbstractInteractiveShell::setPromptPrefix(const QString &prefix)
{
    m_promptPrefix = prefix;
}

QString AbstractInteractiveShell::promptPrefix() const
{
    return m_promptPrefix;
}

void AbstractInteractiveShell::setRootCommand(InteractiveCommand *rootCommand)
{
    if (m_rootCommand)
        m_rootCommand->deleteLater();

    m_rootCommand = rootCommand;
}

void AbstractInteractiveShell::run()
{
    prompt();
}

void AbstractInteractiveShell::run(const QString &command)
{
    run();
    parse(command);
}

void AbstractInteractiveShell::run(const QStringList &commands)
{
    run();
    parse(commands);
}

void AbstractInteractiveShell::parse(const QString &line)
{
    QStringList args = line.split(" ");
    parse(args);
}

void AbstractInteractiveShell::parse(const QStringList &args)
{
    if (args.isEmpty())
        return;

    if (m_rootCommand && !m_rootCommand->parse(args))
        qDebug() << "command not found";
}

void AbstractInteractiveShell::prompt()
{
    QTextStream out(stdout);
    out << promptPrefix();
}

} // namespace InteractiveShell
} // namespace Engnr
