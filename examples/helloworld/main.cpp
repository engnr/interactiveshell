#include <QCoreApplication>
#include "interactiveshell.h"
#include "commands.h"

using namespace Engnr::InteractiveShell;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InteractiveShell shell;
    shell.setRootCommand(new Commands);
    shell.run();

    return a.exec();
}
