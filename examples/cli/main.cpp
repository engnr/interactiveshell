#include <QCoreApplication>
#include "interactiveshell.h"

using namespace Engnr::InteractiveShell;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InteractiveShell shell;
    shell.run();

    return a.exec();
}
