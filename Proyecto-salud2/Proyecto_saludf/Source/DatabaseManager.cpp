/**
 * @file DatabaseManager.cpp
 * @brief Implementación de la clase DatabaseManager para gestionar la base de datos en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QSqlRecord>
#include <QDateTime>
#include <QVariant>

/**
 * @brief Obtiene la instancia única de DatabaseManager.
 * @return Referencia a la instancia singleton.
 *
 * Implementa el patrón singleton para garantizar una única instancia de la clase.
 */
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

/**
 * @brief Constructor privado de la clase DatabaseManager.
 *
 * Inicializa la base de datos al crear la instancia singleton.
 */
DatabaseManager::DatabaseManager()
{
    initializeDatabase();
}

/**
 * @brief Destructor de la clase DatabaseManager.
 *
 * Cierra la conexión a la base de datos si está abierta.
 */
DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

/**
 * @brief Inicializa la conexión a la base de datos y crea las tablas necesarias.
 * @return true si la inicialización es exitosa, false en caso contrario.
 *
 * Configura la base de datos SQLite y crea las tablas 'users' y 'health_records' si no existen.
 */
bool DatabaseManager::initializeDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("health_app.db");

    if (!db.open()) {
        qDebug() << "Error al abrir la base de datos:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    if (db.tables().contains("health_records")) {
        query.exec("ALTER TABLE health_records RENAME TO health_records_old");
        query.exec("CREATE TABLE health_records ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "user_id INTEGER NOT NULL, "
                   "date_time DATETIME NOT NULL, "
                   "weight REAL, "
                   "blood_pressure TEXT, "
                   "glucose_level REAL, "
                   "FOREIGN KEY (user_id) REFERENCES users(id))");
        query.exec("INSERT INTO health_records (id, user_id, date_time, weight, blood_pressure, glucose_level) "
                   "SELECT id, user_id, date_time, weight, CAST(blood_pressure AS TEXT), glucose_level "
                   "FROM health_records_old");
        query.exec("DROP TABLE health_records_old");
    }

    bool success = query.exec("CREATE TABLE IF NOT EXISTS users ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "username TEXT UNIQUE NOT NULL COLLATE NOCASE, "
                            "password TEXT NOT NULL)");

    if (!success) {
        qDebug() << "Error al crear la tabla de usuarios:" << query.lastError().text();
        return false;
    }

    success = query.exec("CREATE TABLE IF NOT EXISTS health_records ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                       "user_id INTEGER NOT NULL, "
                       "date_time DATETIME NOT NULL, "
                       "weight REAL, "
                       "blood_pressure TEXT, "
                       "glucose_level REAL, "
                       "FOREIGN KEY (user_id) REFERENCES users(id))");

    if (!success) {
        qDebug() << "Error al crear la tabla de registros de salud:" << query.lastError().text();
        return false;
    }

    qDebug() << "Base de datos inicializada correctamente";
    return true;
}

/**
 * @brief Verifica las credenciales de un usuario.
 * @param username Nombre de usuario.
 * @param password Contraseña del usuario.
 * @return true si las credenciales son válidas, false en caso contrario.
 *
 * Compara el hash SHA-256 de la contraseña ingresada con la almacenada en la base de datos.
 */
bool DatabaseManager::checkCredentials(const QString& username, const QString& password)
{
    if (!db.isOpen() && !db.open()) {
        qDebug() << "No se pudo abrir la base de datos para verificar credenciales:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    qDebug() << "Intentando autenticar usuario:" << username;
    qDebug() << "Contraseña ingresada (hasheada):" << hashedPassword;

    query.prepare("SELECT COUNT(*) FROM users WHERE LOWER(username) = LOWER(:username) AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (!query.exec()) {
        qDebug() << "Error al verificar credenciales:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "Usuarios encontrados con las credenciales:" << count;
        if (count > 0) {
            qDebug() << "Autenticación exitosa para:" << username;
            return true;
        }
    }

    qDebug() << "No se encontraron usuarios con esas credenciales";
    QSqlQuery debugQuery;
    debugQuery.prepare("SELECT password FROM users WHERE LOWER(username) = LOWER(:username)");
    debugQuery.bindValue(":username", username);
    if (debugQuery.exec() && debugQuery.next()) {
        qDebug() << "Contraseña almacenada en la base de datos:" << debugQuery.value(0).toString();
    } else {
        qDebug() << "Usuario no encontrado en la base de datos o error en la consulta:" << debugQuery.lastError().text();
    }
    return false;
}

/**
 * @brief Registra un nuevo usuario en la base de datos.
 * @param username Nombre de usuario.
 * @param password Contraseña del usuario.
 * @return true si el registro es exitoso, false en caso contrario.
 *
 * Almacena la contraseña como un hash SHA-256 y verifica que el nombre de usuario sea único.
 */
bool DatabaseManager::registerUser(const QString& username, const QString& password)
{
    if (!db.isOpen() && !db.open()) {
        qDebug() << "No se pudo abrir la base de datos para registrar usuario:" << db.lastError().text();
        return false;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM users WHERE LOWER(username) = LOWER(:username)");
    checkQuery.bindValue(":username", username);

    if (!checkQuery.exec()) {
        qDebug() << "Error al verificar si el usuario existe:" << checkQuery.lastError().text();
        return false;
    }

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        qDebug() << "El usuario ya existe:" << username;
        return false;
    }

    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    qDebug() << "Registrando usuario:" << username << "con contraseña hasheada:" << hashedPassword;

    QSqlDatabase::database().transaction();
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", hashedPassword);

    bool success = insertQuery.exec();
    if (!success) {
        qDebug() << "Error al registrar usuario:" << insertQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return false;
    }

    QSqlDatabase::database().commit();
    qDebug() << "Usuario registrado exitosamente:" << username;
    return true;
}

/**
 * @brief Obtiene los datos de un usuario por su nombre de usuario.
 * @param username Nombre de usuario.
 * @return Objeto User con los datos del usuario, o un objeto vacío si no se encuentra.
 */
User DatabaseManager::getUserByUsername(const QString& username)
{
    if (!db.isOpen() && !db.open()) {
        qDebug() << "No se pudo abrir la base de datos para obtener usuario:" << db.lastError().text();
        return User();
    }

    QSqlQuery query;
    query.prepare("SELECT id, username, password FROM users WHERE LOWER(username) = LOWER(:username)");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error al buscar usuario:" << query.lastError().text();
        return User();
    }

    if (query.next()) {
        QString id = query.value(0).toString();
        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        qDebug() << "Usuario encontrado: ID =" << id << ", Username =" << username;
        return User(id, username, password);
    }

    qDebug() << "Usuario no encontrado:" << username;
    return User();
}

/**
 * @brief Añade un registro de salud a la base de datos.
 * @param record Registro de salud a añadir.
 * @return true si el registro se añade correctamente, false en caso contrario.
 *
 * Inserta el registro en la tabla health_records usando una transacción.
 */
bool DatabaseManager::addhealthrecord(const healthrecord& record)
{
    if (!db.isOpen() && !db.open()) {
        qDebug() << "No se pudo abrir la base de datos para agregar registro de salud:" << db.lastError().text();
        return false;
    }

    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.prepare("INSERT INTO health_records (user_id, date_time, weight, blood_pressure, glucose_level) "
                  "VALUES (:user_id, :date_time, :weight, :blood_pressure, :glucose_level)");
    query.bindValue(":user_id", record.getUserId());
    query.bindValue(":date_time", record.getDateTime());
    query.bindValue(":weight", record.getWeight());
    query.bindValue(":blood_pressure", record.getBloodPressure());
    query.bindValue(":glucose_level", record.getGlucose());

    bool success = query.exec();
    if (!success) {
        qDebug() << "Error al guardar registro de salud:" << query.lastError().text();
        QSqlDatabase::database().rollback();
        return false;
    }

    QSqlDatabase::database().commit();
    qDebug() << "Registro de salud guardado para user_id:" << record.getUserId();
    return true;
}

/**
 * @brief Calcula el promedio de un campo específico para un usuario.
 * @param field Campo de la base de datos (por ejemplo, "weight", "glucose_level").
 * @param userId Identificador del usuario.
 * @return Valor promedio del campo especificado, o 0 si no hay datos.
 *
 * Para presión arterial, calcula el promedio de la presión sistólica.
 */
double DatabaseManager::calculateAverage(const QString& field, int userId)
{
    if (!db.isOpen() && !db.open()) {
        qDebug() << "No se pudo abrir la base de datos para calcular promedio:" << db.lastError().text();
        return 0.0;
    }

    QString queryField;
    if (field == "weight") {
        queryField = "weight";
    } else if (field == "blood_pressure") {
        queryField = "CAST(SUBSTR(blood_pressure, 1, INSTR(blood_pressure, '/') - 1) AS REAL)";
    } else if (field == "glucose_level") {
        queryField = "glucose_level";
    } else {
        qDebug() << "Campo no válido para calcular promedio:" << field;
        return 0.0;
    }

    QSqlQuery query;
    QString queryStr = QString("SELECT AVG(%1) FROM health_records WHERE user_id = :user_id").arg(queryField);
    query.prepare(queryStr);
    query.bindValue(":user_id", userId);

    qDebug() << "Ejecutando consulta para promedio:" << queryStr << "con user_id:" << userId;

    if (!query.exec()) {
        qDebug() << "Error al calcular promedio:" << query.lastError().text();
        return 0.0;
    }

    if (query.next()) {
        double result = query.value(0).toDouble();
        qDebug() << "Promedio calculado para" << queryField << ":" << result;
        return result;
    }

    qDebug() << "No se encontraron datos para calcular el promedio";
    return 0.0;
}

/**
 * @brief Obtiene los registros de salud de un usuario.
 * @param userId Identificador del usuario.
 * @return Vector de registros de salud asociados al usuario.
 */
QVector<healthrecord> DatabaseManager::getHealthRecordsByUserId(int userId)
{
    QVector<healthrecord> records;

    if (!db.isOpen() && !db.open()) {
        qDebug() << "No se pudo abrir la base de datos para obtener los registros de salud:" << db.lastError().text();
        return records;
    }

    QSqlQuery query;
    query.prepare("SELECT id, user_id, date_time, weight, blood_pressure, glucose_level "
                  "FROM health_records WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << "Error al obtener los registros de salud:" << query.lastError().text();
        return records;
    }

    while (query.next()) {
        QString id = query.value(0).toString();
        QString userIdStr = query.value(1).toString();
        QDateTime dateTime = query.value(2).toDateTime();
        float weight = query.value(3).toFloat();
        QString bloodPressure = query.value(4).toString();
        float glucoseLevel = query.value(5).toFloat();

        healthrecord record(id, userIdStr, dateTime, weight, bloodPressure, glucoseLevel);
        records.append(record);
    }

    qDebug() << "Registros obtenidos para user_id:" << userId << ", Total:" << records.size();
    return records;
}

/**
 * @brief Obtiene la conexión a la base de datos.
 * @return Objeto QSqlDatabase que representa la conexión activa.
 */
QSqlDatabase DatabaseManager::getDatabase()
{
    return db;
}
