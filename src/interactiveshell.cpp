#include "interactiveshell.h"

#include <QDebug>

namespace Engnr {
namespace InteractiveShell {

InteractiveShell::InteractiveShell(QObject *parent) :
    AbstractInteractiveShell(parent)
{
}

void InteractiveShell::run()
{
    prompt();
}

void InteractiveShell::parse(const QByteArray &line)
{
    qDebug() << "Received:" << line;
}

} // namespace InteractiveShell
} // namespace Engnr

