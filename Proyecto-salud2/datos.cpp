#include "datos.h"
#include "ui_datos.h"
#include "DatabaseManager.h"
#include "CSVExporter.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QFileDialog>
#include <QTimer>

datos::datos(QWidget *parent, const QString& userId) :
    QWidget(parent),
    ui(new Ui::datos),
    currentUserId(userId),
    model(nullptr),
    welcomeMessageShown(false)
{
    ui->setupUi(this);

    // Aplicar hoja de estilo
    this->setStyleSheet(
        "QWidget {"
        "    background-color: #F5F7FA;"
        "}"
        "QTabWidget::pane {"
        "    border: 1px solid #D3D3D3;"
        "    background: #FFFFFF;"
        "}"
        "QTabBar::tab {"
        "    padding: 8px 16px;"
        "    border-top-left-radius: 4px;"
        "    border-top-right-radius: 4px;"
        "    color: white;"
        "}"
        "QTabBar::tab:first {"
        "    background: #4CAF50;"
        "}"
        "QTabBar::tab:first:selected {"
        "    background: #388E3C;"
        "}"
        "QTabBar::tab:nth-child(2) {"
        "    background: #2196F3;"
        "}"
        "QTabBar::tab:nth-child(2):selected {"
        "    background: #1976D2;"
        "}"
        "QTabBar::tab:last {"
        "    background: #757575;"
        "}"
        "QTabBar::tab:last:selected {"
        "    background: #616161;"
        "}"
        "QTabBar::tab:hover {"
        "    background: #B0BEC5;"
        "}"
        "QTableView {"
        "    background-color: #FFFFFF;"
        "    alternate-background-color: #E8ECEF;"
        "    border: 1px solid #D3D3D3;"
        "    gridline-color: #D3D3D3;"
        "}"
        "QTableView::item:selected {"
        "    background-color: #BBDEFB;"
        "    color: black;"
        "}"
        "QHeaderView::section {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    padding: 4px;"
        "    border: 1px solid #D3D3D3;"
        "}"
        "QLineEdit, QDateTimeEdit {"
        "    background-color: #FFFFFF;"
        "    border: 1px solid #D3D3D3;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "}"
        "QLineEdit:focus, QDateTimeEdit:focus {"
        "    border: 1px solid #2196F3;"
        "}"
        "QComboBox#comboBox {"
        "    background-color: #FFFFFF;"
        "    border: 1px solid #D3D3D3;"
        "    border-radius: 4px;"
        "    padding: 6px;"
        "    color: #212121;"
        "    font-size: 14px;"
        "}"
        "QComboBox#comboBox:hover {"
        "    border: 1px solid #2196F3;"
        "}"
        "QComboBox#comboBox:focus {"
        "    border: 1px solid #2196F3;"
        "}"
        "QComboBox#comboBox::drop-down {"
        "    width: 20px;"
        "    border: none;"
        "}"
        "QComboBox#comboBox QAbstractItemView {"
        "    background-color: #FFFFFF;"
        "    color: #212121;"
        "    selection-background-color: #BBDEFB;"
        "    selection-color: #212121;"
        "    border: 1px solid #D3D3D3;"
        "    padding: 4px;"
        "}"
        "QComboBox#comboBox QAbstractItemView::item {"
        "    padding: 6px;"
        "    min-height: 24px;"
        "}"
        "QComboBox#comboBox QAbstractItemView::item:hover {"
        "    background-color: #E3F2FD;"
        "    color: #212121;"
        "}"
        "QComboBox#comboBox QAbstractItemView::item:selected {"
        "    background-color: #BBDEFB;"
        "    color: #212121;"
        "}"
        "QPushButton#guardarbutton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "}"
        "QPushButton#guardarbutton:hover {"
        "    background-color: #388E3C;"
        "}"
        "QPushButton#guardarbutton:pressed {"
        "    background-color: #2E7D32;"
        "}"
        "QPushButton#promediarButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "}"
        "QPushButton#promediarButton:hover {"
        "    background-color: #1976D2;"
        "}"
        "QPushButton#promediarButton:pressed {"
        "    background-color: #1565C0;"
        "}"
        "QPushButton#Exportar {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "}"
        "QPushButton#Exportar:hover {"
        "    background-color: #1976D2;"
        "}"
        "QPushButton#Exportar:pressed {"
        "    background-color: #1565C0;"
        "}"
        "QPushButton#btnCerrarSesion {"
        "    background-color: #F44336;"
        "    color: white;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "}"
        "QPushButton#btnCerrarSesion:hover {"
        "    background-color: #D32F2F;"
        "}"
        "QPushButton#btnCerrarSesion:pressed {"
        "    background-color: #B71C1C;"
        "}"
        "QLabel {"
        "    color: #212121;"
        "    font-size: 14px;"
        "}"
    );

    // Establecer la fecha y hora actual
    ui->fechahoraInput->setDateTime(QDateTime::currentDateTime());

    // Configurar ComboBox
    ui->comboBox->setEnabled(true);
    ui->comboBox->setFocusPolicy(Qt::StrongFocus);
    ui->comboBox->addItem("Peso (Kg)", "weight");
    ui->comboBox->addItem("Presión Arterial", "blood_pressure");
    ui->comboBox->addItem("Nivel de Glucosa", "glucose_level");

    // Conectar botones
    connect(ui->btnCerrarSesion, &QPushButton::clicked, this, &datos::onbtnCerrarSesionClicked);
    connect(ui->guardarbutton, &QPushButton::clicked, this, &datos::onGuardarClicked);
    connect(ui->promediarButton, &QPushButton::clicked, this, &datos::onPromediarClicked);
    connect(ui->Exportar, &QPushButton::clicked, this, &datos::onExportButtonClicked);

    // Configurar tabla
    setupModelAndView();

    // Mostrar mensaje de bienvenida
    QTimer::singleShot(100, this, [=]() {
        if (!welcomeMessageShown) {
            welcomeMessageShown = true;
            QSqlQuery query(DatabaseManager::instance().getDatabase());
            query.prepare("SELECT username FROM users WHERE id = :userId");
            query.bindValue(":userId", currentUserId.toInt());
            if (query.exec() && query.next()) {
                QString username = query.value(0).toString();
                QMessageBox::information(this, "Bienvenido", "Has iniciado sesión como: " + username);
            } else {
                qDebug() << "Error al obtener nombre de usuario para user_id:" << currentUserId << ", Error:" << query.lastError().text();
                QMessageBox::warning(this, "Advertencia", "No se pudo obtener el nombre de usuario.");
            }
        }
    });

    this->setFocus();
    this->activateWindow();
}

datos::~datos()
{
    delete ui;
    if (model) {
        delete model;
    }
}

void datos::setupModelAndView()
{
    qDebug() << "Configurando modelo para user_id:" << currentUserId;

    model = new QSqlQueryModel(this);
    QString queryStr = QString(
        "SELECT hr.id, hr.user_id, u.username, hr.date_time, hr.weight, hr.blood_pressure, hr.glucose_level "
        "FROM health_records hr "
        "JOIN users u ON hr.user_id = u.id "
        "WHERE hr.user_id = %1"
    ).arg(currentUserId.toInt());
    model->setQuery(queryStr, DatabaseManager::instance().getDatabase());

    if (model->lastError().isValid()) {
        qDebug() << "Error al cargar datos en la tabla:" << model->lastError().text();
    } else {
        qDebug() << "Datos cargados en la tabla. Filas:" << model->rowCount();
    }

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "User ID");
    model->setHeaderData(2, Qt::Horizontal, "Username");
    model->setHeaderData(3, Qt::Horizontal, "Fecha/Hora");
    model->setHeaderData(4, Qt::Horizontal, "Peso (kg)");
    model->setHeaderData(5, Qt::Horizontal, "Presión Arterial");
    model->setHeaderData(6, Qt::Horizontal, "Nivel Glucosa");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
}

void datos::onGuardarClicked()
{
    QString weight = ui->pesoInput->text();
    QString bloodPressure = ui->presionInput->text();
    QString glucose = ui->glucosaInput->text();
    QDateTime dateTime = ui->fechahoraInput->dateTime();

    if (weight.isEmpty() || bloodPressure.isEmpty() || glucose.isEmpty()) {
        QMessageBox::warning(this, "Datos incompletos", "Por favor completa todos los campos.");
        return;
    }

    bool weightOk, glucoseOk;
    float weightVal = weight.toFloat(&weightOk);
    float glucoseVal = glucose.toFloat(&glucoseOk);

    if (!weightOk || !glucoseOk) {
        QMessageBox::warning(this, "Datos inválidos", "Por favor ingresa valores numéricos válidos para peso y glucosa.");
        return;
    }

    if (!bloodPressure.contains("/")) {
        QMessageBox::warning(this, "Datos inválidos", "La presión arterial debe tener el formato 'sistólica/diastólica'.");
        return;
    }

    healthrecord record("", currentUserId, dateTime, weightVal, bloodPressure, glucoseVal);

    if (DatabaseManager::instance().addhealthrecord(record)) {
        QMessageBox::information(this, "Éxito", "Registro guardado correctamente.");
        ui->pesoInput->clear();
        ui->presionInput->clear();
        ui->glucosaInput->clear();
        ui->fechahoraInput->setDateTime(QDateTime::currentDateTime());

        QString queryStr = QString(
            "SELECT hr.id, hr.user_id, u.username, hr.date_time, hr.weight, hr.blood_pressure, hr.glucose_level "
            "FROM health_records hr "
            "JOIN users u ON hr.user_id = u.id "
            "WHERE hr.user_id = %1"
        ).arg(currentUserId.toInt());
        model->setQuery(queryStr, DatabaseManager::instance().getDatabase());
        if (model->lastError().isValid()) {
            qDebug() << "Error al actualizar la tabla después de guardar:" << model->lastError().text();
        }
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar el registro.");
    }
}

void datos::onbtnCerrarSesionClicked()
{
    emit cerrarSesion();
    this->close();
}

void datos::onPromediarClicked()
{
    QString selectedField = ui->comboBox->currentData().toString();
    double promedio = DatabaseManager::instance().calculateAverage(selectedField, currentUserId.toInt());
    QString fieldText = ui->comboBox->currentText();
    QMessageBox::information(this, "Promedio Calculado",
                             "El promedio de " + fieldText + " es: " + QString::number(promedio, 'f', 2));
}

void datos::onExportButtonClicked()
{
    QVector<healthrecord> records = DatabaseManager::instance().getHealthRecordsByUserId(currentUserId.toInt());
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar como CSV", "", "Archivos CSV (*.csv)");
    if (filePath.isEmpty()) {
        return;
    }
    if (CSVExporter::exportToCSV(filePath, records)) {
        QMessageBox::information(this, "Éxito", "Datos exportados a CSV correctamente.");
    } else {
        QMessageBox::warning(this, "Error", "No se pudo exportar los datos a CSV.");
    }
}
