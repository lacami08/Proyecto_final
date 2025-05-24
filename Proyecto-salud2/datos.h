#ifndef DATOS_H
#define DATOS_H

#include <QWidget>
#include <QSqlQueryModel>
#include "healthrecord.h"

namespace Ui {
class datos;
}

class datos : public QWidget
{
    Q_OBJECT

public:
    explicit datos(QWidget *parent = nullptr, const QString& userId = "");
    ~datos();

signals:
    void cerrarSesion();

private slots:
    void onbtnCerrarSesionClicked();
    void onGuardarClicked();
    void onPromediarClicked();
    void onExportButtonClicked();

private:
    Ui::datos *ui;
    QString currentUserId;
    QSqlQueryModel *model;
    bool welcomeMessageShown; // Bandera para evitar mensajes duplicados
    void setupModelAndView();
};

#endif // DATOS_H
