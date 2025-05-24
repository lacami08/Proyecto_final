#ifndef HEALTHANALYZER_H
#define HEALTHANALYZER_H

#include "healthrecord.h"
#include "DatabaseManager.h"
#include <QVector>

class HealthAnalyzer {
public:
    HealthAnalyzer(int userId);

    // Promedios
    float averageWeight() const;
    float averageGlucose() const;
    float averageBloodPressure() const;

    // Tendencias
    float weightTrend() const;
    float glucoseTrend() const;
    float bloodPressureTrend() const;

private:
    QVector<healthrecord> m_records;

    float calculateTrend(const QVector<float>& values) const;
};

#endif // HEALTHANALYZER_H
