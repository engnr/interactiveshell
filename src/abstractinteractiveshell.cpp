#include "abstractinteractiveshell.h"

#include <unistd.h>

namespace Engnr {
namespace InteractiveShell {

AbstractInteractiveShell::AbstractInteractiveShell(QObject *parent) :
    QObject(parent),
    m_notifier(STDIN_FILENO, QSocketNotifier::Read),
    m_promptPrefix(">>> ")
{
    connect(&m_notifier, &QSocketNotifier::activated,
            this, &AbstractInteractiveShell::read);
}

void AbstractInteractiveShell::setPromptPrefix(const QString &prefix)
{
    m_promptPrefix = prefix;
}

QString AbstractInteractiveShell::promptPrefix() const
{
    return m_promptPrefix;
}

void AbstractInteractiveShell::read(int)
{
    QTextStream in(stdin);
    QByteArray line = in.readLine().toLatin1();
    parse(line);
    prompt();
}

void AbstractInteractiveShell::prompt()
{
    QTextStream out(stdout);
    out << promptPrefix();
}

} // namespace InteractiveShell
} // namespace Engnr
