#ifndef ROOTCOMMAND_H
#define ROOTCOMMAND_H

#include "interactivecommand.h"

namespace Engnr {
namespace InteractiveShell {

class RootCommand : public InteractiveCommand
{
    Q_OBJECT
public:
    explicit RootCommand(QObject *parent = 0);

public slots:
    void quitCommand();
    QString quitHelp();
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // ROOTCOMMAND_H
