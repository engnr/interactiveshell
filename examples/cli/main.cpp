#include <QCoreApplication>
#include "interactiveshell.h"
#include "rootcommand.h"

using namespace Engnr::InteractiveShell;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InteractiveShell shell;
    shell.setRootCommand(new RootCommand);
    shell.run();

    return a.exec();
}
