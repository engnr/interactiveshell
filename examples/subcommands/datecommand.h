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

    void nextCommand()
    {
        QDate date = QDate::currentDate();
        do {
            printLine(QString("Next weekday is %1")
                      .arg(QDate::longDayName(date.dayOfWeek())));
            date = date.addDays(1);
        } while(yes("Show next day?"));
    }

    QString nextHelp() const
    {
        return QString("Next weekday");
    }
};

#endif // DATECOMMAND_H
