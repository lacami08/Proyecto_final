#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include "healthrecord.h"
#include <QString>
#include <QVector>

class CSVExporter {
public:
    static bool exportToCSV(const QString& filePath, const QVector<healthrecord>& records);
};

#endif // CSVEXPORTER_H
