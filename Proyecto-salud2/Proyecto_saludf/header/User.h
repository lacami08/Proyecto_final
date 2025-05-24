/**
 * @file User.h
 * @brief Declaración de la clase User para representar un usuario en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef USER_H
#define USER_H

#include <QString>

/**
 * @class User
 * @brief Clase que representa un usuario de la aplicación.
 *
 * Almacena información básica del usuario, como su identificador, nombre de usuario y contraseña.
 */
class User
{
public:
    /**
     * @brief Constructor por defecto de la clase User.
     */
    User();

    /**
     * @brief Constructor con parámetros de la clase User.
     * @param id Identificador único del usuario.
     * @param username Nombre de usuario.
     * @param password Contraseña del usuario.
     */
    User(const QString& id, const QString& username, const QString& password);

    /**
     * @brief Obtiene el identificador del usuario.
     * @return Identificador único del usuario.
     */
    QString getId() const;

    /**
     * @brief Obtiene el nombre de usuario.
     * @return Nombre de usuario.
     */
    QString getUsername() const;

    /**
     * @brief Obtiene la contraseña del usuario.
     * @return Contraseña del usuario.
     */
    QString getPassword() const;

    /**
     * @brief Establece el identificador del usuario.
     * @param id Nuevo identificador del usuario.
     */
    void setId(const QString& id);

    /**
     * @brief Establece el nombre de usuario.
     * @param username Nuevo nombre de usuario.
     */
    void setUsername(const QString& username);

    /**
     * @brief Establece la contraseña del usuario.
     * @param password Nueva contraseña del usuario.
     */
    void setPassword(const QString& password);

private:
    /**
     * @brief Identificador único del usuario.
     */
    QString m_id;

    /**
     * @brief Nombre de usuario.
     */
    QString m_username;

    /**
     * @brief Contraseña del usuario.
     */
    QString m_password;
};

#endif // USER_H
