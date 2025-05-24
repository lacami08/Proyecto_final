/**
 * @file registro.h
 * @brief Declaración de la clase registro para la ventana de registro de usuarios en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef REGISTRO_H
#define REGISTRO_H

#include <QWidget>

namespace Ui {
class registro;
}

/**
 * @class registro
 * @brief Clase que gestiona la ventana de registro de usuarios en la aplicación Rastreador Personal de Salud.
 *
 * Esta clase representa la interfaz gráfica para que los usuarios puedan registrarse en la aplicación,
 * proporcionando credenciales que se almacenan en la base de datos. Hereda de QWidget para proporcionar
 * una ventana personalizada basada en Qt.
 */
class registro : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase registro.
     * @param parent Puntero al widget padre, por defecto nullptr.
     */
    explicit registro(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase registro.
     *
     * Libera los recursos asociados con la interfaz de la ventana de registro.
     */
    ~registro();

signals:
    /**
     * @brief Señal emitida cuando la ventana de registro se cierra.
     *
     * Esta señal permite notificar a otras partes de la aplicación que la ventana de registro
     * ha sido cerrada, por ejemplo, para volver a la ventana principal.
     */
    void registroCerrado();

private slots:
    /**
     * @brief Slot para manejar el clic en el botón de registro.
     *
     * Valida los datos ingresados por el usuario y, si son correctos, los almacena en la base de datos.
     */
    void on_rebutton2_clicked();

    /**
     * @brief Slot para manejar el clic en el botón de cancelar.
     *
     * Cierra la ventana de registro y emite la señal registroCerrado().
     */
    void on_cabutton_clicked();

private:
    /**
     * @brief Puntero a la interfaz de usuario generada por Qt Designer para la ventana de registro.
     */
    Ui::registro *ui;

    /**
     * @brief Bandera para evitar la ejecución múltiple de eventos.
     *
     * Evita que los slots se ejecuten más de una vez simultáneamente, asegurando un manejo seguro
     * de los eventos de la interfaz.
     */
    bool isProcessing;
};

#endif // REGISTRO_H
