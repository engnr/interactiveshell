#ifndef COMMANDS_H
#define COMMANDS_H

#include "rootcommand.h"

class Commands : public Engnr::InteractiveShell::RootCommand
{
    Q_OBJECT
public slots:
    void greenCommand()
    {
        setColor(Engnr::InteractiveShell::Color::green());
        printLine("Green");
        clearColor();
    }

    QString greenHelp() const
    {
        return "Green";
    }

    void redCommand()
    {
        setColor(Engnr::InteractiveShell::Color::red());
        printLine("Red");
        clearColor();
    }

    QString redHelp() const
    {
        return "Red";
    }

    void yellowCommand()
    {
        setColor(Engnr::InteractiveShell::Color::yellow());
        printLine("Yellow");
        clearColor();
    }

    QString yellowHelp() const
    {
        return "Yellow";
    }
};

#endif // COMMANDS_H
