/**
 * @file MainWindow.cpp
 * @brief Implementación de la clase MainWindow para la interfaz principal del Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QDebug>
#include <QDir>

/**
 * @brief Constructor de la clase MainWindow.
 * @param parent Puntero al widget padre, por defecto nullptr.
 *
 * Inicializa la interfaz principal, aplica estilos visuales, verifica la existencia de la base de datos
 * y conecta los botones de inicio de sesión y registro.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , registroWindow(nullptr)
    , datosWindow(nullptr)
    , isProcessing(false)
{
    ui->setupUi(this);

    this->setWindowTitle("Rastreador Personal de Salud");

    // Aplicar hoja de estilo
    this->setStyleSheet(
        "QMainWindow {"
        "    background-color: #F5F7FA;" // Fondo gris claro
        "}"
        "QLineEdit {"
        "    background-color: #FFFFFF;" // Fondo blanco
        "    border: 1px solid #D3D3D3;" // Borde gris
        "    border-radius: 4px;" // Bordes redondeados
        "    padding: 6px;" // Espaciado
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #2196F3;" // Borde azul al enfocar
        "}"
        "QPushButton#inibutton, QPushButton#rebutton {"
        "    background-color: #2196F3;" // Azul para botones
        "    color: white;" // Texto blanco
        "    border-radius: 4px;" // Bordes redondeados
        "    padding: 8px 16px;" // Espaciado
        "    border: none;" // Sin borde
        "}"
        "QPushButton#inibutton:hover, QPushButton#rebutton:hover {"
        "    background-color: #1976D2;" // Azul oscuro al pasar el ratón
        "}"
        "QPushButton#inibutton:pressed, QPushButton#rebutton:pressed {"
        "    background-color: #1565C0;" // Azul más oscuro al clic
        "}"
        "QLabel {"
        "    color: #212121;" // Texto negro para etiquetas
        "    font-size: 16px;" // Tamaño legible
        "}"
    );

    if (QFile::exists("health_app.db")) {
        qDebug() << "✅ Base de datos encontrada y lista para usar.";
    } else {
        qDebug() << "⚠️ Archivo de base de datos no encontrado. Se creará uno nuevo.";
    }

    // Desconectar cualquier conexión automática
    disconnect(ui->inibutton, &QPushButton::clicked, this, &MainWindow::on_inibutton_clicked);
    // Conectar explícitamente solo el botón
    connect(ui->inibutton, &QPushButton::clicked, this, &MainWindow::on_inibutton_clicked);
    connect(ui->rebutton, &QPushButton::clicked, this, &MainWindow::on_rebutton_clicked);

    // Configurar el botón como no predeterminado
    ui->inibutton->setDefault(false);
    ui->inibutton->setAutoDefault(false);
}

/**
 * @brief Destructor de la clase MainWindow.
 *
 * Libera los recursos de la interfaz y las ventanas secundarias.
 */
MainWindow::~MainWindow()
{
    delete ui;
    if (registroWindow) {
        delete registroWindow;
    }
    if (datosWindow) {
        delete datosWindow;
    }
}

/**
 * @brief Slot para manejar el clic en el botón de registro.
 *
 * Oculta la ventana principal, crea y muestra la ventana de registro, y conecta la señal
 * registroCerrado para volver a mostrar la ventana principal al cerrar la de registro.
 */
void MainWindow::on_rebutton_clicked()
{
    this->hide();
    if (!registroWindow) {
        registroWindow = new registro(nullptr);
        connect(registroWindow, &registro::registroCerrado, this, [=]() {
            this->show();
            registroWindow->deleteLater();
            registroWindow = nullptr;
        });
        registroWindow->setAttribute(Qt::WA_DeleteOnClose);
    }
    registroWindow->show();
}

/**
 * @brief Slot para manejar el clic en el botón de iniciar sesión.
 *
 * Valida las credenciales ingresadas, muestra la ventana de datos si son correctas, o un mensaje
 * de error si no lo son. Utiliza isProcessing para evitar clics múltiples.
 */
void MainWindow::on_inibutton_clicked()
{
    if (isProcessing) {
        qDebug() << "Procesamiento en curso, ignorando clic adicional.";
        return;
    }

    isProcessing = true;
    qDebug() << "Iniciando procesamiento de inicio de sesión";

    QString username = ui->lineEditusuario->text();
    QString password = ui->lineEditcontrasena->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Por favor, completa todos los campos.");
        isProcessing = false;
        return;
    }

    DatabaseManager& dbManager = DatabaseManager::instance();
    if (dbManager.checkCredentials(username, password)) {
        User user = dbManager.getUserByUsername(username);
        qDebug() << "Usuario autenticado. ID:" << user.getId() << ", Username:" << user.getUsername();

        this->hide();
        if (!datosWindow) {
            datosWindow = new datos(nullptr, user.getId());
            connect(datosWindow, &datos::cerrarSesion, this, [=]() {
                this->show();
                ui->lineEditcontrasena->clear();
                datosWindow->deleteLater();
                datosWindow = nullptr;
            });
            datosWindow->setAttribute(Qt::WA_DeleteOnClose);
        }
        datosWindow->show();
    } else {
        QMessageBox::critical(this, "Error", "Usuario o contraseña incorrectos.");
    }

    isProcessing = false;
    qDebug() << "Procesamiento de inicio de sesión finalizado";
}
