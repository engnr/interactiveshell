#ifndef COMMANDS_H
#define COMMANDS_H

#include "rootcommand.h"
#include "user.h"

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
            say() << "try: adduser John Doe";
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
            say() << "try: adduser John Doe 30";
    }

    QString addUserHelp() const
    {
        return QString("Add new user");
    }

    void usersCommand() const
    {
        if (m_users.isEmpty()) {
            say() << "No users";
            return;
        }

        for (const User &user : m_users) {
            say() << "First name:" << user.firstName();
            say() << "Last name:" << user.lastName();
            if (user.hasAge())
                say() << "Age:" << user.age();
            say() << "-----";
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
