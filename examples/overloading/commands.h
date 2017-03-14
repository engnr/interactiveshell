#ifndef COMMANDS_H
#define COMMANDS_H

#include "rootcommand.h"
#include "user.h"
#include <QDebug>

class Commands : public Engnr::InteractiveShell::RootCommand
{
    Q_OBJECT
public slots:
    void addUserCommand(const QVariant &firstName, const QVariant &lastName)
    {
        User user;
        if (user.setFirstName(firstName) && user.setLastName(lastName))
            m_users << user;
        else
            printLine("");
    }

    void addUserCommand(const QVariant &firstName, const QVariant &lastName,
                        const QVariant &age)
    {
        User user;
        if (user.setFirstName(firstName)
                && user.setLastName(lastName)
                && user.setAge(age))
            m_users << user;
        else
            printLine("");
    }

    QString addUserHelp() const
    {
        return QString("Add new user");
    }

    void usersCommand() const
    {
        if (m_users.isEmpty()) {
            qDebug() << "No users";
            return;
        }

        for (const User &user : m_users) {
            qDebug() << "First name:" << user.firstName();
            qDebug() << "Last name:" << user.lastName();
            if (user.hasAge())
                qDebug() << "Age:" << user.age();
            qDebug() << "\n";
        }
    }

    QString usersHelp() const
    {
        return QString("Show user list");
    }

private:
    QList<User> m_users;
};

#endif // COMMANDS_H
