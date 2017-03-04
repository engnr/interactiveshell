#ifndef INTERACTIVESHELL_H
#define INTERACTIVESHELL_H

#include "abstractinteractiveshell.h"
#include <QSocketNotifier>

namespace Engnr {
namespace InteractiveShell {

class InteractiveShell : public AbstractInteractiveShell
{
    Q_OBJECT
public:
    explicit InteractiveShell(QObject *parent = 0);

private slots:
    void read();

private:
    QSocketNotifier m_notifier;
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVESHELL_H
