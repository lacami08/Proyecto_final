/**
 * @file healthrecord.h
 * @brief Declaración de la clase healthrecord para representar un registro de salud en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef HEALTHRECORD_H
#define HEALTHRECORD_H

#include <QString>
#include <QDateTime>
#include <QUuid>

/**
 * @class healthrecord
 * @brief Clase que representa un registro individual de datos de salud de un usuario.
 *
 * Almacena información como peso, glucosa, presión arterial y la fecha/hora del registro,
 * asociada a un usuario específico.
 */
class healthrecord
{
public:
    /**
     * @brief Constructor de la clase healthrecord.
     * @param id Identificador único del registro.
     * @param userId Identificador del usuario asociado al registro.
     * @param dateTime Fecha y hora del registro.
     * @param weight Peso del usuario en kilogramos.
     * @param bloodPressure Presión arterial del usuario (formato sistólica/diastólica).
     * @param glucose Nivel de glucosa en sangre del usuario.
     */
    healthrecord(const QString& id, const QString& userId, const QDateTime& dateTime,
                 float weight, const QString& bloodPressure, float glucose);

    /**
     * @brief Obtiene el identificador único del registro.
     * @return Identificador del registro.
     */
    QString getId() const;

    /**
     * @brief Obtiene el identificador del usuario asociado.
     * @return Identificador del usuario.
     */
    QString getUserId() const;

    /**
     * @brief Obtiene la fecha y hora del registro.
     * @return Fecha y hora del registro.
     */
    QDateTime getDateTime() const;

    /**
     * @brief Obtiene el peso registrado.
     * @return Peso en kilogramos.
     */
    float getWeight() const;

    /**
     * @brief Obtiene la presión arterial registrada.
     * @return Presión arterial en formato sistólica/diastólica.
     */
    QString getBloodPressure() const;

    /**
     * @brief Obtiene el nivel de glucosa registrado.
     * @return Nivel de glucosa en sangre.
     */
    float getGlucose() const;

private:
    /**
     * @brief Identificador único del registro.
     */
    QString m_id;

    /**
     * @brief Identificador del usuario asociado al registro.
     */
    QString m_userId;

    /**
     * @brief Fecha y hora del registro.
     */
    QDateTime m_dateTime;

    /**
     * @brief Peso del usuario en kilogramos.
     */
    float m_weight;

    /**
     * @brief Presión arterial del usuario (formato sistólica/diastólica).
     */
    QString m_bloodPressure;

    /**
     * @brief Nivel de glucosa en sangre del usuario.
     */
    float m_glucose;
};

#endif // HEALTHRECORD_H
