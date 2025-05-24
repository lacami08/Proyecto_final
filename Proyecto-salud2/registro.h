#ifndef REGISTRO_H
#define REGISTRO_H

#include <QWidget>

namespace Ui {
class registro;
}

class registro : public QWidget
{
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    ~registro();

signals:
    void registroCerrado();

private slots:
    void on_rebutton2_clicked();
    void on_cabutton_clicked();

private:
    Ui::registro *ui;
    bool isProcessing; // Declarar la bandera isProcessing
};

#endif // REGISTRO_H
