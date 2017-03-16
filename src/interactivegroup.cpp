#include "interactivegroup.h"

#include <QMetaMethod>

namespace Engnr {
namespace InteractiveShell {

void InteractiveGroup::run()
{
    for (int i = metaObject()->methodOffset(); i < metaObject()->methodCount(); i++) {
        QMetaMethod method = metaObject()->method(i);
        if (method.access() == QMetaMethod::Public
                && method.methodType() == QMetaMethod::Slot
                && method.parameterCount() == 0)
        {
            method.invoke(this, Qt::DirectConnection);
        }
    }
}

} // namespace InteractiveShell
} // namespace Engnr
