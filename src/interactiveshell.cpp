#include "interactiveshell.h"

#include <QDebug>
#include <unistd.h>

namespace Engnr {
namespace InteractiveShell {

InteractiveShell::InteractiveShell(QObject *parent) :
    AbstractInteractiveShell(parent),
    m_notifier(STDIN_FILENO, QSocketNotifier::Read)
{
    connect(&m_notifier, &QSocketNotifier::activated,
            this, &InteractiveShell::read);
}

void InteractiveShell::read()
{
    QTextStream in(stdin);
    parse(in.readLine());
}

} // namespace InteractiveShell
} // namespace Engnr

