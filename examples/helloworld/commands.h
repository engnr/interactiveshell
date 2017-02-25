#ifndef COMMANDS_H
#define COMMANDS_H

#include "rootcommand.h"

class Commands : public Engnr::InteractiveShell::RootCommand
{
    Q_OBJECT
public slots:
    QString helloHelp() const
    {
        return QString("Prints \"Hello, world\"");
    }
    void helloCommand()
    {
        printLine("Hello, world!");
    }
};

#endif // COMMANDS_H
