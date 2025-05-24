#include "registro.h"
#include "ui_registro.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QDebug>

registro::registro(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registro)
    , isProcessing(false) // Inicializar isProcessing
{
    ui->setupUi(this);

    // Aplicar hoja de estilo
    this->setStyleSheet(
        "QWidget {"
        "    background-color: #F5F7FA;"
        "}"
        "QLineEdit {"
        "    background-color: #FFFFFF;"
        "    border: 1px solid #D3D3D3;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "}"
        "QLineEdit:focus {"
        "    border: 1px solid #2196F3;"
        "}"
        "QPushButton#rebutton2 {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "}"
        "QPushButton#rebutton2:hover {"
        "    background-color: #388E3C;"
        "}"
        "QPushButton#rebutton2:pressed {"
        "    background-color: #2E7D32;"
        "}"
        "QPushButton#cabutton {"
        "    background-color: #757575;"
        "    color: white;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "}"
        "QPushButton#cabutton:hover {"
        "    background-color: #616161;"
        "}"
        "QPushButton#cabutton:pressed {"
        "    background-color: #424242;"
        "}"
        "QLabel {"
        "    color: #212121;"
        "    font-size: 16px;"
        "}"
    );

    // Desconectar cualquier conexión previa para evitar duplicados
    disconnect(ui->rebutton2, &QPushButton::clicked, 0, 0);
    connect(ui->rebutton2, &QPushButton::clicked, this, &registro::on_rebutton2_clicked);
    connect(ui->cabutton, &QPushButton::clicked, this, &registro::on_cabutton_clicked);
}

registro::~registro() {
    delete ui;
}

void registro::on_rebutton2_clicked() {
    // Evitar procesamiento múltiple
    if (isProcessing) {
        qDebug() << "Clic ignorado: procesamiento en curso";
        return;
    }
    isProcessing = true;

    QString username = ui->lineEditusuario2->text().trimmed();
    QString password = ui->lineEditcontrasena2->text();
    QString confirmPassword = ui->lineEditconficontrasena->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos son obligatorios.");
        isProcessing = false;
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::critical(this, "Error", "Las contraseñas no coinciden.");
        isProcessing = false;
        return;
    }

    DatabaseManager& dbManager = DatabaseManager::instance();
    qDebug() << "Intentando registrar usuario:" << username;

    bool registered = dbManager.registerUser(username, password);
    qDebug() << "Resultado de registerUser:" << registered;

    if (registered) {
        qDebug() << "Mostrando mensaje de éxito";
        QMessageBox::information(this, "Registro Exitoso", "Usuario registrado correctamente.");
        qDebug() << "Emitiendo registroCerrado y cerrando ventana";
        emit registroCerrado();
        this->close();
    } else {
        qDebug() << "Mostrando mensaje de error";
        QMessageBox::critical(this, "Error", "No se pudo registrar el usuario. Intenta con otro nombre.");
    }

    isProcessing = false;
}

void registro::on_cabutton_clicked() {
    emit registroCerrado();
    this->close();
}
