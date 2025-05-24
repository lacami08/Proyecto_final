#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registro.h"
#include "datos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inibutton_clicked();
    void on_rebutton_clicked();

private:
    Ui::MainWindow *ui;
    registro *registroWindow;
    datos *datosWindow;
    bool isProcessing; // Bandera para evitar doble ejecución

};
#endif // MAINWINDOW_H
