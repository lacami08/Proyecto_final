/**
 * @file MainWindow.h
 * @brief Declaración de la clase MainWindow para la interfaz principal del Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registro.h"
#include "datos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Clase principal que gestiona la ventana inicial de la aplicación Rastreador Personal de Salud.
 *
 * Esta clase representa la interfaz principal de la aplicación, que incluye la autenticación de usuarios
 * y la navegación hacia las ventanas de registro de usuarios y visualización de datos de salud.
 * Hereda de QMainWindow para proporcionar una interfaz gráfica basada en Qt.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase MainWindow.
     * @param parent Puntero al widget padre, por defecto nullptr.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor de la clase MainWindow.
     *
     * Libera los recursos asociados con la interfaz y las ventanas secundarias.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot para manejar el clic en el botón de iniciar sesión.
     *
     * Valida las credenciales del usuario y, si son correctas, muestra la ventana de datos.
     */
    void on_inibutton_clicked();

    /**
     * @brief Slot para manejar el clic en el botón de registro.
     *
     * Abre la ventana de registro para permitir la creación de un nuevo usuario.
     */
    void on_rebutton_clicked();

private:
    /**
     * @brief Puntero a la interfaz de usuario generada por Qt Designer.
     */
    Ui::MainWindow *ui;

    /**
     * @brief Puntero a la ventana de registro de usuarios.
     */
    registro *registroWindow;

    /**
     * @brief Puntero a la ventana de visualización de datos de salud.
     */
    datos *datosWindow;

    /**
     * @brief Bandera para evitar la ejecución múltiple de eventos.
     *
     * Evita que los slots se ejecuten más de una vez simultáneamente, por ejemplo, para prevenir
     * mensajes dobles de "Usuario no encontrado" durante el inicio de sesión.
     */
    bool isProcessing;
};

#endif // MAINWINDOW_H
