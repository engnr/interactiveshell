#ifndef INTERACTIVESHELL_H
#define INTERACTIVESHELL_H

#include "abstractinteractiveshell.h"

namespace Engnr {
namespace InteractiveShell {

class InteractiveCommand;

class InteractiveShell : public AbstractInteractiveShell
{
    Q_OBJECT
public:
    explicit InteractiveShell(QObject *parent = 0);
    void run();
    void setRootCommand(InteractiveCommand *rootCommand);

private:
    void parse(const QByteArray &command);

    InteractiveCommand *m_rootCommand;
};

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVESHELL_H
