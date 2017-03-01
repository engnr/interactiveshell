#include "interactiveshellapplication.h"

namespace Engnr {
namespace InteractiveShell {

InteractiveShellApplication::InteractiveShellApplication(int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
    m_shell.run();
}

void InteractiveShellApplication::setRootCommand(InteractiveCommand *rootCommand)
{
    m_shell.setRootCommand(rootCommand);
}

} // namespace InteractiveShell
} // namespace Engnr
