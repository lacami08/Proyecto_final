#include "CSVExporter.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

bool CSVExporter::exportToCSV(const QString& filePath, const QVector<healthrecord>& records) {
    // Abrir el archivo CSV
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << file.errorString();
        return false;
    }

    // Crear un flujo de texto para escribir en el archivo
    QTextStream out(&file);

    // Escribir la cabecera del CSV
    out << "ID,User ID,DateTime,Weight,Blood Pressure,Glucose Level\n";

    // Escribir cada registro
    for (const healthrecord& record : records) {
        // Escapar comas en blood_pressure para evitar problemas en el CSV
        QString bloodPressure = QString(record.getBloodPressure()).replace(",", ";");
        out << QString("%1,%2,%3,%4,%5,%6\n")
               .arg(record.getId())
               .arg(record.getUserId())
               .arg(record.getDateTime().toString("yyyy-MM-dd hh:mm:ss"))
               .arg(record.getWeight())
               .arg(bloodPressure)
               .arg(record.getGlucose());
    }

    file.close();
    return true;
}
