#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    User(const QString& id, const QString& username, const QString& password);

    QString getId() const;
    QString getUsername() const;
    QString getPassword() const;

    void setId(const QString& id);
    void setUsername(const QString& username);
    void setPassword(const QString& password);

private:
    QString m_id;
    QString m_username;
    QString m_password;
};

#endif // USER_H
