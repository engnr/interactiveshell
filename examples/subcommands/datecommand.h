#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "interactivecommand.h"
#include <QDate>

class Date : public Engnr::InteractiveShell::InteractiveCommand
{
    Q_OBJECT
public:
    QString description() const
    {
        return QString("Date commands");
    }

public slots:
    void currentCommand()
    {
        printLine(QDate::currentDate().toString());
    }

    QString currentHelp() const
    {
        return QString("Current date");
    }
};

#endif // DATECOMMAND_H
