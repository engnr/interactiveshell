#include "rootcommand.h"

#include <QCoreApplication>

namespace Engnr {
namespace InteractiveShell {

RootCommand::RootCommand(QObject *parent) :
    InteractiveCommand(parent)
{
}

void RootCommand::quitCommand()
{
    QCoreApplication::quit();
}

QString RootCommand::quitHelp()
{
    return QString("Quit from application");
}

} // namespace InteractiveShell
} // namespace Engnr
