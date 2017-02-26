#ifndef NEWYEARCOMMAND_H
#define NEWYEARCOMMAND_H

#include "interactivecommand.h"
#include <QDate>
#include <QDebug>

class NewYear : public Engnr::InteractiveShell::InteractiveCommand
{
    Q_OBJECT
public:
    void run()
    {
        QDate current = QDate::currentDate();
        QDate newYear(current.year() + 1, 1, 1);
        qDebug() << current.daysTo(newYear);
    }

    QString description() const
    {
        return QString("How many days until New Year's Day");
    }
};

#endif // NEWYEARCOMMAND_H
