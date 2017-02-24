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

} // namespace InteractiveShell
} // namespace Engnr
