#ifndef COMMANDS_H
#define COMMANDS_H

#include "rootcommand.h"

using namespace Engnr::InteractiveShell;

class Commands : public Engnr::InteractiveShell::RootCommand
{
    Q_OBJECT
public slots:
    void greenCommand()
    {
        setColor(Color::green());
        setColor(Color::onWhite());
        say() << "Green";
        clearColor();
    }

    QString greenHelp() const
    {
        return "Green";
    }

    void redCommand()
    {
        say() << Color::red() << "Red" << Color::clear();
    }

    QString redHelp() const
    {
        return "Red";
    }

    void yellowCommand()
    {
        say("Yellow", Color::yellow() | Color::onMagenta());
    }

    QString yellowHelp() const
    {
        return "Yellow";
    }
};

#endif // COMMANDS_H
