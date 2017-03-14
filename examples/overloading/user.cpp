#include "user.h"


User::User() :
    m_age(0)
{
}

bool User::setFirstName(const QVariant &firstName)
{
    QString s = firstName.toString();
    if (isName(s)) {
        m_firstName = s;
        return true;
    }

    return false;
}

QString User::firstName() const
{
    return m_firstName;
}

bool User::setLastName(const QVariant &lastName)
{
    QString s = lastName.toString();
    if (isName(s)) {
        m_lastName = s;
        return true;
    }

    return false;
}

QString User::lastName() const
{
    return m_lastName;
}

bool User::setAge(const QVariant &age)
{
    bool ok;
    int a = age.toInt(&ok);
    if (ok && a > 0 && a < 120) {
        m_age = a;
        return true;
    }

    return false;
}

int User::age() const
{
    return m_age;
}

bool User::hasAge() const
{
    return m_age > 0;
}

bool User::isName(const QString &name) const
{
    QRegExp rx("^[A-Za-z]+$");
    return rx.exactMatch(name);
}
