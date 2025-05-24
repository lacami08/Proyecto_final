#include "HealthAnalyzer.h"
#include "DatabaseManager.h"
#include <QDebug>

HealthAnalyzer::HealthAnalyzer(int userId) {
    m_records = DatabaseManager::instance().getHealthRecordsByUserId(userId);
    qDebug() << "HealthAnalyzer inicializado para user_id:" << userId << ", Registros cargados:" << m_records.size();
}

// --- Promedios ---
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

// Métodos de tendencia (sin implementar por ahora)
float HealthAnalyzer::weightTrend() const { return 0; }
float HealthAnalyzer::glucoseTrend() const { return 0; }
float HealthAnalyzer::bloodPressureTrend() const { return 0; }
float HealthAnalyzer::calculateTrend(const QVector<float>& values) const {
    Q_UNUSED(values); // Suprimir advertencia de parámetro no usado
    return 0;
}
