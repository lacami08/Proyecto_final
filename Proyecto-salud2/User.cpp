#include "User.h"

User::User()
    : m_id(""), m_username(""), m_password("")
{
}

User::User(const QString& id, const QString& username, const QString& password)
    : m_id(id), m_username(username), m_password(password)
{
}

QString User::getId() const
{
    return m_id;
}

QString User::getUsername() const
{
    return m_username;
}

QString User::getPassword() const
{
    return m_password;
}

void User::setId(const QString& id)
{
    m_id = id;
}

void User::setUsername(const QString& username)
{
    m_username = username;
}

void User::setPassword(const QString& password)
{
    m_password = password;
}
