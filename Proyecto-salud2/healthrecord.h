#ifndef HEALTHRECORD_H
#define HEALTHRECORD_H

#include <QString>
#include <QDateTime>
#include <QUuid>

class healthrecord
{
public:
    // Constructor con ID de la base de datos
    healthrecord(const QString& id, const QString& userId, const QDateTime& dateTime,
                 float weight, const QString& bloodPressure, float glucose);

    // Getters
    QString getId() const;
    QString getUserId() const;
    QDateTime getDateTime() const;
    float getWeight() const;
    QString getBloodPressure() const;
    float getGlucose() const;

private:
    QString m_id;
    QString m_userId;
    QDateTime m_dateTime;
    float m_weight;
    QString m_bloodPressure; // Cambiado de float a QString
    float m_glucose;
};

#endif // HEALTHRECORD_H
