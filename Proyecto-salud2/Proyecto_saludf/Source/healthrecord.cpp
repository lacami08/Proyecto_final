/**
 * @file healthrecord.cpp
 * @brief Implementación de la clase healthrecord para representar un registro de salud en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#include "healthrecord.h"
#include <QUuid>

/**
 * @brief Constructor de la clase healthrecord.
 * @param id Identificador único del registro.
 * @param userId Identificador del usuario asociado al registro.
 * @param dateTime Fecha y hora del registro.
 * @param weight Peso del usuario en kilogramos.
 * @param bloodPressure Presión arterial del usuario (formato sistólica/diastólica).
 * @param glucose Nivel de glucosa en sangre del usuario.
 *
 * Inicializa los atributos del registro de salud con los valores proporcionados.
 */
healthrecord::healthrecord(const QString& id, const QString& userId, const QDateTime& dateTime,
                           float weight, const QString& bloodPressure, float glucose)
    : m_id(id), m_userId(userId), m_dateTime(dateTime), m_weight(weight),
      m_bloodPressure(bloodPressure), m_glucose(glucose)
{
}

/**
 * @brief Obtiene el identificador único del registro.
 * @return Identificador del registro.
 */
QString healthrecord::getId() const
{
    return m_id;
}

/**
 * @brief Obtiene el identificador del usuario asociado.
 * @return Identificador del usuario.
 */
QString healthrecord::getUserId() const
{
    return m_userId;
}

/**
 * @brief Obtiene la fecha y hora del registro.
 * @return Fecha y hora del registro.
 */
QDateTime healthrecord::getDateTime() const
{
    return m_dateTime;
}

/**
 * @brief Obtiene el peso registrado.
 * @return Peso en kilogramos.
 */
float healthrecord::getWeight() const
{
    return m_weight;
}

/**
 * @brief Obtiene la presión arterial registrada.
 * @return Presión arterial en formato sistólica/diastólica.
 */
QString healthrecord::getBloodPressure() const
{
    return m_bloodPressure;
}

/**
 * @brief Obtiene el nivel de glucosa registrado.
 * @return Nivel de glucosa en sangre.
 */
float healthrecord::getGlucose() const
{
    return m_glucose;
}
