#ifndef USER_H
#define USER_H

#include <QVariant>


class User
{
public:
    User();
    bool setFirstName(const QVariant &firstName);
    QString firstName() const;
    bool setLastName(const QVariant &lastName);
    QString lastName() const;
    bool setAge(const QVariant &age);
    int age() const;
    bool hasAge() const;

private:
    bool isName(const QString &name) const;
    QString m_firstName;
    QString m_lastName;
    int m_age;
};

#endif // USER_H
