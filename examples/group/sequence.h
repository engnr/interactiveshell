#ifndef GROUP_H
#define GROUP_H

#include "interactivegroup.h"

class Sequence : public Engnr::InteractiveShell::InteractiveGroup
{
    Q_OBJECT
public slots:
    QString description() const
    {
        return QString("Print sequence");
    }

    void first()
    {
        say() << 1;
    }

    void second()
    {
        say() << 2;
    }

    void third()
    {
        say() << 3;
    }
};

#endif // GROUP_H
