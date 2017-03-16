#ifndef INTERACTIVESHELLAPPLICATION_H
#define INTERACTIVESHELLAPPLICATION_H

#include <QCoreApplication>
#include "interactiveshell.h"

namespace Engnr {
namespace InteractiveShell {

class InteractiveShellApplication : public QCoreApplication
{
    Q_OBJECT
public:
    InteractiveShellApplication(int &argc, char **argv);
    void setRootCommand(InteractiveCommand *rootCommand);

private slots:
    void run();

private:
    InteractiveShell m_shell;
};

#define INTERACTIVESHELL_MAIN(RootCommand) \
    int main(int argc, char *argv[]) { \
        Engnr::InteractiveShell::InteractiveShellApplication a(argc, argv); \
        a.setRootCommand(new RootCommand); \
        return a.exec(); \
    }

} // namespace InteractiveShell
} // namespace Engnr

#endif // INTERACTIVESHELLAPPLICATION_H
