/**
 * @file DatabaseManager.h
 * @brief Declaración de la clase DatabaseManager para gestionar la base de datos en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "healthrecord.h"
#include "User.h"

/**
 * @class DatabaseManager
 * @brief Clase singleton para gestionar la conexión y operaciones con la base de datos.
 *
 * Proporciona métodos para inicializar la base de datos, autenticar usuarios, registrar usuarios
 * y gestionar registros de salud.
 */
class DatabaseManager
{
public:
    /**
     * @brief Obtiene la instancia única de DatabaseManager.
     * @return Referencia a la instancia singleton.
     */
    static DatabaseManager& instance();

    /**
     * @brief Destructor de la clase DatabaseManager.
     *
     * Cierra la conexión a la base de datos y libera recursos.
     */
    ~DatabaseManager();

    /**
     * @brief Inicializa la conexión a la base de datos.
     * @return true si la inicialización es exitosa, false en caso contrario.
     */
    bool initializeDatabase();

    /**
     * @brief Verifica las credenciales de un usuario.
     * @param username Nombre de usuario.
     * @param password Contraseña del usuario.
     * @return true si las credenciales son válidas, false en caso contrario.
     */
    bool checkCredentials(const QString& username, const QString& password);

    /**
     * @brief Registra un nuevo usuario en la base de datos.
     * @param username Nombre de usuario.
     * @param password Contraseña del usuario.
     * @return true si el registro es exitoso, false en caso contrario.
     */
    bool registerUser(const QString& username, const QString& password);

    /**
     * @brief Obtiene los datos de un usuario por su nombre de usuario.
     * @param username Nombre de usuario.
     * @return Objeto User con los datos del usuario.
     */
    User getUserByUsername(const QString& username);

    /**
     * @brief Añade un registro de salud a la base de datos.
     * @param record Registro de salud a añadir.
     * @return true si el registro se añade correctamente, false en caso contrario.
     */
    bool addhealthrecord(const healthrecord& record);

    /**
     * @brief Calcula el promedio de un campo específico para un usuario.
     * @param field Campo de la base de datos (por ejemplo, "weight", "glucose").
     * @param userId Identificador del usuario.
     * @return Valor promedio del campo especificado.
     */
    double calculateAverage(const QString& field, int userId);

    /**
     * @brief Obtiene los registros de salud de un usuario.
     * @param userId Identificador del usuario.
     * @return Vector de registros de salud asociados al usuario.
     */
    QVector<healthrecord> getHealthRecordsByUserId(int userId);

    /**
     * @brief Obtiene la conexión a la base de datos.
     * @return Objeto QSqlDatabase que representa la conexión activa.
     */
    QSqlDatabase getDatabase();

private:
    /**
     * @brief Constructor privado para implementar el patrón singleton.
     */
    DatabaseManager();

    /**
     * @brief Conexión a la base de datos.
     */
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
