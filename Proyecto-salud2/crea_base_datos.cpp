#include "crea_base_datos.h"
#include "QDir"
#include <QDebug>

QSqlDatabase crea_base_datos::_db = QSqlDatabase::addDatabase("QSQLITE");
crea_base_datos *crea_base_datos::_obj = new crea_base_datos;

crea_base_datos::crea_base_datos(QObject *parent)
    : QObject{parent}
{
    _db.setDatabaseName(QDir::currentPath() + "/datos_salud.sqlite");

    if(_db.open()){
        qDebug() << "Conexión a la base de datos exitosa =>" + _db.databaseName() + "<=";
    }

    else{
        qDebug() << "Problemas para conectar a la base de datos" + _db.databaseName();
    }
}

crea_base_datos *crea_base_datos::obj()
{
    if(!_obj){
        _obj=new crea_base_datos();
    }
    return _obj;
}

QSqlDatabase crea_base_datos::db()
{
    return _db;
}
