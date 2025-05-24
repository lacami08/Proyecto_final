/**
 * @file CSVExporter.h
 * @brief Declaración de la clase CSVExporter para exportar registros de salud a formato CSV.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include "healthrecord.h"
#include <QString>
#include <QVector>

/**
 * @class CSVExporter
 * @brief Clase para exportar registros de salud a un archivo CSV.
 *
 * Proporciona una interfaz estática para exportar un conjunto de registros de salud
 * a un archivo en formato CSV.
 */
class CSVExporter {
public:
    /**
     * @brief Exporta registros de salud a un archivo CSV.
     * @param filePath Ruta del archivo CSV donde se guardarán los datos.
     * @param records Vector de registros de salud a exportar.
     * @return true si la exportación es exitosa, false en caso contrario.
     */
    static bool exportToCSV(const QString& filePath, const QVector<healthrecord>& records);
};

#endif // CSVEXPORTER_H
