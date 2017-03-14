#include "interactiveshellapplication.h"

namespace Engnr {
namespace InteractiveShell {

InteractiveShellApplication::InteractiveShellApplication(int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
    QMetaObject::invokeMethod(this, "run", Qt::QueuedConnection);
}

void InteractiveShellApplication::setRootCommand(InteractiveCommand *rootCommand)
{
    m_shell.setRootCommand(rootCommand);
}

void InteractiveShellApplication::run()
{
    QStringList args = arguments();
    args.removeFirst();
    if (args.isEmpty()) {
        m_shell.run();
    } else {
        m_shell.run(args);
        quit();
    }
}

} // namespace InteractiveShell
} // namespace Engnr
