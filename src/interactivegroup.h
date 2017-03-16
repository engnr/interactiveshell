#ifndef INTERACTIVEGROUP_H
#define INTERACTIVEGROUP_H

#include "interactivecommand.h"

namespace Engnr {
namespace InteractiveShell {

class InteractiveGroup : public InteractiveCommand
{
    Q_OBJECT
public:
    void run();
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVEGROUP_H
