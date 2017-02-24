#ifndef INTERACTIVESHELL_H
#define INTERACTIVESHELL_H

#include "abstractinteractiveshell.h"

namespace Engnr {
namespace InteractiveShell {

class InteractiveShell : public AbstractInteractiveShell
{
    Q_OBJECT
public:
    explicit InteractiveShell(QObject *parent = 0);
    void run();

private:
    void parse(const QByteArray &line);
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVESHELL_H
