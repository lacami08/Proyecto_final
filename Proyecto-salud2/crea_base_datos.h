#ifndef CREA_BASE_DATOS_H
#define CREA_BASE_DATOS_H

#include <QObject>
#include <QSqlDatabase>

class crea_base_datos : public QObject
{
    Q_OBJECT
public:
    explicit crea_base_datos(QObject *parent = 0);

    static crea_base_datos *_obj; // <- método para obtener la instancia única
    static QSqlDatabase db();

    static crea_base_datos *obj();  // <- única instancia
    static QSqlDatabase _db;         // <- conexión a base de datos
};

#endif // CREA_BASE_DATOS_H
