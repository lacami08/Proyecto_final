/**
 * @file datos.h
 * @brief Declaración de la clase datos para la ventana de gestión de datos de salud en el Rastreador Personal de Salud.
 * @author TuNombre
 * @date 2025-05-24
 */

#ifndef DATOS_H
#define DATOS_H

#include <QWidget>
#include <QSqlQueryModel>
#include "healthrecord.h"

namespace Ui {
class datos;
}

/**
 * @class datos
 * @brief Clase que gestiona la ventana de visualización y edición de datos de salud del usuario.
 *
 * Esta clase representa la interfaz gráfica donde los usuarios pueden ver, guardar, promediar y exportar
 * sus datos de salud almacenados en la base de datos. Hereda de QWidget para proporcionar una ventana
 * personalizada basada en Qt.
 */
class datos : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de la clase datos.
     * @param parent Puntero al widget padre, por defecto nullptr.
     * @param userId Identificador del usuario autenticado para cargar sus datos de salud.
     */
    explicit datos(QWidget *parent = nullptr, const QString& userId = "");

    /**
     * @brief Destructor de la clase datos.
     *
     * Libera los recursos asociados con la interfaz y el modelo de datos.
     */
    ~datos();

signals:
    /**
     * @brief Señal emitida cuando el usuario cierra la sesión.
     *
     * Notifica a otras partes de la aplicación que la sesión del usuario ha finalizado,
     * permitiendo regresar a la ventana principal.
     */
    void cerrarSesion();

private slots:
    /**
     * @brief Slot para manejar el clic en el botón de cerrar sesión.
     *
     * Cierra la sesión del usuario actual y emite la señal cerrarSesion().
     */
    void onbtnCerrarSesionClicked();

    /**
     * @brief Slot para manejar el clic en el botón de guardar.
     *
     * Almacena los datos de salud ingresados por el usuario en la base de datos.
     */
    void onGuardarClicked();

    /**
     * @brief Slot para manejar el clic en el botón de promediar.
     *
     * Calcula y muestra el promedio de los datos de salud del usuario.
     */
    void onPromediarClicked();

    /**
     * @brief Slot para manejar el clic en el botón de exportar.
     *
     * Exporta los datos de salud del usuario a un formato externo, como un archivo.
     */
    void onExportButtonClicked();

private:
    /**
     * @brief Puntero a la interfaz de usuario generada por Qt Designer para la ventana de datos.
     */
    Ui::datos *ui;

    /**
     * @brief Identificador del usuario autenticado actualmente.
     */
    QString currentUserId;

    /**
     * @brief Modelo de datos para interactuar con la base de datos y mostrar los registros de salud.
     */
    QSqlQueryModel *model;

    /**
     * @brief Bandera para evitar la repetición del mensaje de bienvenida.
     *
     * Garantiza que el mensaje de bienvenida se muestre solo una vez al abrir la ventana.
     */
    bool welcomeMessageShown;

    /**
     * @brief Configura el modelo de datos y la vista para mostrar los registros de salud.
     *
     * Inicializa el modelo QSqlQueryModel y lo conecta con la interfaz gráfica para mostrar
     * los datos de salud del usuario.
     */
    void setupModelAndView();
};

#endif // DATOS_H
