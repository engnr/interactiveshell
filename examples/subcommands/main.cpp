#include <QCoreApplication>

#include "interactiveshell.h"
#include "rootcommand.h"
#include "timecommand.h"
#include "datecommand.h"
#include "newyearcommand.h"

using namespace Engnr::InteractiveShell;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RootCommand *rootCommand = new RootCommand;
    rootCommand->addCommand(new Time);
    rootCommand->addCommand(new Date);
    rootCommand->addCommand(new NewYear);

    InteractiveShell shell;
    shell.setRootCommand(rootCommand);
    shell.run();

    return a.exec();
}
