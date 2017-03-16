#include "interactiveshellapplication.h"
#include "sequence.h"
#include "rootcommand.h"

using namespace Engnr::InteractiveShell;

int main(int argc, char *argv[])
{
    InteractiveShellApplication a(argc, argv);
    RootCommand *rootCommand = new RootCommand;
    rootCommand->addCommand(new Sequence);
    a.setRootCommand(rootCommand);
    return a.exec();
}
