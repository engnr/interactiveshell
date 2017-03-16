#include "interactiveshellapplication.h"
#include "rootcommand.h"

class Commands : public Engnr::InteractiveShell::RootCommand
{
    Q_OBJECT
public slots:
    void helloCommand()
    {
        say() << "Hello, world";
    }
    QString helloHelp() const
    {
        return QString("Prints 'Hello, world'");
    }
};

INTERACTIVESHELL_MAIN(Commands)
#include "main.moc"

