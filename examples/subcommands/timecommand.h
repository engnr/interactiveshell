#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

#include "interactivecommand.h"
#include <QTime>

class Time : public Engnr::InteractiveShell::InteractiveCommand
{
    Q_OBJECT
public:
    QString description() const
    {
        return QString("Time commands");
    }

public slots:
    void currentCommand()
    {
        printLine(QTime::currentTime().toString());
    }

    QString currentHelp() const
    {
        return QString("Current time");
    }
};

#endif // TIMECOMMAND_H
