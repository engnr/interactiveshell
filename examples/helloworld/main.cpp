#include "interactiveshellapplication.h"
#include "commands.h"

using namespace Engnr::InteractiveShell;

int main(int argc, char *argv[])
{
    InteractiveShellApplication a(argc, argv);
    a.setRootCommand(new Commands);
    return a.exec();
}
