/**
 * @file HealthAnalyzer.h
 * @brief Declaración de la clase HealthAnalyzer para analizar datos de salud en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef HEALTHANALYZER_H
#define HEALTHANALYZER_H

#include "healthrecord.h"
#include "DatabaseManager.h"
#include <QVector>

/**
 * @class HealthAnalyzer
 * @brief Clase para analizar los registros de salud de un usuario.
 *
 * Esta clase calcula promedios y tendencias de los datos de salud (peso, glucosa, presión arterial)
 * basándose en los registros almacenados para un usuario específico.
 */
class HealthAnalyzer {
public:
    /**
     * @brief Constructor de la clase HealthAnalyzer.
     * @param userId Identificador del usuario cuyos datos de salud se analizarán.
     */
    HealthAnalyzer(int userId);

    /**
     * @brief Calcula el promedio del peso del usuario.
     * @return Valor promedio del peso, o 0 si no hay registros.
     */
    float averageWeight() const;

    /**
     * @brief Calcula el promedio de los niveles de glucosa del usuario.
     * @return Valor promedio de glucosa, o 0 si no hay registros.
     */
    float averageGlucose() const;

    /**
     * @brief Calcula el promedio de la presión arterial del usuario.
     * @return Valor promedio de presión arterial, o 0 si no hay registros.
     */
    float averageBloodPressure() const;

    /**
     * @brief Calcula la tendencia del peso del usuario.
     * @return Valor de la tendencia del peso, basado en los registros disponibles.
     */
    float weightTrend() const;

    /**
     * @brief Calcula la tendencia de los niveles de glucosa del usuario.
     * @return Valor de la tendencia de glucosa, basado en los registros disponibles.
     */
    float glucoseTrend() const;

    /**
     * @brief Calcula la tendencia de la presión arterial del usuario.
     * @return Valor de la tendencia de presión arterial, basado en los registros disponibles.
     */
    float bloodPressureTrend() const;

private:
    /**
     * @brief Vector que almacena los registros de salud del usuario.
     */
    QVector<healthrecord> m_records;

    /**
     * @brief Calcula la tendencia de una serie de valores.
     * @param values Vector de valores numéricos para analizar la tendencia.
     * @return Valor de la tendencia calculada.
     */
    float calculateTrend(const QVector<float>& values) const;
};

#endif // HEALTHANALYZER_H
