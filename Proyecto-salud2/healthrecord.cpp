#include "healthrecord.h"
#include <QUuid>

healthrecord::healthrecord(const QString& id, const QString& userId, const QDateTime& dateTime,
                           float weight, const QString& bloodPressure, float glucose)
    : m_id(id), m_userId(userId), m_dateTime(dateTime), m_weight(weight),
      m_bloodPressure(bloodPressure), m_glucose(glucose)
{
}

QString healthrecord::getId() const
{
    return m_id;
}

QString healthrecord::getUserId() const
{
    return m_userId;
}

QDateTime healthrecord::getDateTime() const
{
    return m_dateTime;
}

float healthrecord::getWeight() const
{
    return m_weight;
}

QString healthrecord::getBloodPressure() const
{
    return m_bloodPressure;
}

float healthrecord::getGlucose() const
{
    return m_glucose;
}
