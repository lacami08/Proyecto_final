/**
 * @file User.cpp
 * @brief Implementación de la clase User para representar un usuario en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#include "User.h"

/**
 * @brief Constructor por defecto de la clase User.
 *
 * Inicializa un objeto User con valores vacíos para id, nombre de usuario y contraseña.
 */
User::User()
    : m_id(""), m_username(""), m_password("")
{
}

/**
 * @brief Constructor con parámetros de la clase User.
 * @param id Identificador único del usuario.
 * @param username Nombre de usuario.
 * @param password Contraseña del usuario.
 *
 * Inicializa los atributos del usuario con los valores proporcionados.
 */
User::User(const QString& id, const QString& username, const QString& password)
    : m_id(id), m_username(username), m_password(password)
{
}

/**
 * @brief Obtiene el identificador del usuario.
 * @return Identificador único del usuario.
 */
QString User::getId() const
{
    return m_id;
}

/**
 * @brief Obtiene el nombre de usuario.
 * @return Nombre de usuario.
 */
QString User::getUsername() const
{
    return m_username;
}

/**
 * @brief Obtiene la contraseña del usuario.
 * @return Contraseña del usuario.
 */
QString User::getPassword() const
{
    return m_password;
}

/**
 * @brief Establece el identificador del usuario.
 * @param id Nuevo identificador del usuario.
 */
void User::setId(const QString& id)
{
    m_id = id;
}

/**
 * @brief Establece el nombre de usuario.
 * @param username Nuevo nombre de usuario.
 */
void User::setUsername(const QString& username)
{
    m_username = username;
}

/**
 * @brief Establece la contraseña del usuario.
 * @param password Nueva contraseña del usuario.
 */
void User::setPassword(const QString& password)
{
    m_password = password;
}
