/**
 * @file HealthAnalyzer.cpp
 * @brief Implementación de la clase HealthAnalyzer para analizar datos de salud en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#include "HealthAnalyzer.h"
#include "DatabaseManager.h"
#include <QDebug>

/**
 * @brief Constructor de la clase HealthAnalyzer.
 * @param userId Identificador del usuario cuyos datos de salud se analizarán.
 *
 * Carga los registros de salud del usuario desde la base de datos.
 */
HealthAnalyzer::HealthAnalyzer(int userId) {
    m_records = DatabaseManager::instance().getHealthRecordsByUserId(userId);
    qDebug() << "HealthAnalyzer inicializado para user_id:" << userId << ", Registros cargados:" << m_records.size();
}

/**
 * @brief Calcula el promedio del peso del usuario.
 * @return Valor promedio del peso, o 0 si no hay registros válidos.
 *
 * Ignora valores de peso no válidos (0 o negativos) y registra información de depuración.
 */
float HealthAnalyzer::averageWeight() const {
    if (m_records.isEmpty()) {
        qDebug() << "No hay registros para calcular el promedio de peso";
        return 0;
    }
    float total = 0;
    int count = 0;
    for (const auto& r : m_records) {
        float value = r.getWeight();
        if (value > 0) { // Ignorar valores 0 o negativos
            total += value;
            count++;
            qDebug() << "Peso incluido en promedio:" << value;
        }
    }
    if (count == 0) {
        qDebug() << "No hay valores válidos de peso para promediar";
        return 0;
    }
    float average = total / count;
    qDebug() << "Promedio de peso calculado:" << average << "(Total:" << total << ", Conteo:" << count << ")";
    return average;
}

/**
 * @brief Calcula el promedio de los niveles de glucosa del usuario.
 * @return Valor promedio de glucosa, o 0 si no hay registros válidos.
 *
 * Ignora valores de glucosa no válidos (0 o negativos) y registra información de depuración.
 */
float HealthAnalyzer::averageGlucose() const {
    if (m_records.isEmpty()) {
        qDebug() << "No hay registros para calcular el promedio de glucosa";
        return 0;
    }
    float total = 0;
    int count = 0;
    for (const auto& r : m_records) {
        float value = r.getGlucose();
        if (value > 0) { // Ignorar valores 0 o negativos
            total += value;
            count++;
            qDebug() << "Glucosa incluida en promedio:" << value;
        }
    }
    if (count == 0) {
        qDebug() << "No hay valores válidos de glucosa para promediar";
        return 0;
    }
    float average = total / count;
    qDebug() << "Promedio de glucosa calculado:" << average << "(Total:" << total << ", Conteo:" << count << ")";
    return average;
}

/**
 * @brief Calcula el promedio de la presión arterial (sistólica) del usuario.
 * @return Valor promedio de presión arterial, o 0 si no hay registros válidos.
 *
 * Extrae la presión sistólica del formato "sistólica/diastólica" y registra información de depuración.
 */
float HealthAnalyzer::averageBloodPressure() const {
    if (m_records.isEmpty()) {
        qDebug() << "No hay registros para calcular el promedio de presión arterial";
        return 0;
    }
    float total = 0;
    int count = 0;
    for (const auto& r : m_records) {
        QString bloodPressure = r.getBloodPressure();
        // Extraer la presión sistólica (antes de "/")
        if (bloodPressure.contains("/")) {
            bool ok;
            float value = bloodPressure.split("/")[0].toFloat(&ok);
            if (ok && value > 0) { // Ignorar valores inválidos o negativos
                total += value;
                count++;
                qDebug() << "Presión arterial (sistólica) incluida en promedio:" << value;
            }
        }
    }
    if (count == 0) {
        qDebug() << "No hay valores válidos de presión arterial para promediar";
        return 0;
    }
    float average = total / count;
    qDebug() << "Promedio de presión arterial (sistólica) calculado:" << average << "(Total:" << total << ", Conteo:" << count << ")";
    return average;
}

/**
 * @brief Calcula la tendencia del peso del usuario.
 * @return Valor de la tendencia del peso (sin implementar, retorna 0).
 */
float HealthAnalyzer::weightTrend() const { return 0; }

/**
 * @brief Calcula la tendencia de los niveles de glucosa del usuario.
 * @return Valor de la tendencia de glucosa (sin implementar, retorna 0).
 */
float HealthAnalyzer::glucoseTrend() const { return 0; }

/**
 * @brief Calcula la tendencia de la presión arterial del usuario.
 * @return Valor de la tendencia de presión arterial (sin implementar, retorna 0).
 */
float HealthAnalyzer::bloodPressureTrend() const { return 0; }

/**
 * @brief Calcula la tendencia de una serie de valores.
 * @param values Vector de valores numéricos para analizar la tendencia.
 * @return Valor de la tendencia calculada (sin implementar, retorna 0).
 */
float HealthAnalyzer::calculateTrend(const QVector<float>& values) const {
    Q_UNUSED(values); // Suprimir advertencia de parámetro no usado
    return 0;
}
