#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "healthrecord.h"
#include "User.h"

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    ~DatabaseManager();
    bool initializeDatabase();
    bool checkCredentials(const QString& username, const QString& password);
    bool registerUser(const QString& username, const QString& password);
    User getUserByUsername(const QString& username);
    bool addhealthrecord(const healthrecord& record);
    double calculateAverage(const QString& field, int userId);
    QVector<healthrecord> getHealthRecordsByUserId(int userId);
    QSqlDatabase getDatabase();

private:
    DatabaseManager();
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
