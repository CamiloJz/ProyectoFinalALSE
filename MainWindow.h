/// @file MainWindow.h
/// @brief Declaración de la clase MainWindow para la interfaz principal de la aplicación.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "InventoryManager.h"
#include "ReportGenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// @class MainWindow
/// @brief Clase que representa la ventana principal de la aplicación de inventario.
///
/// Esta clase gestiona la interfaz de usuario, conecta señales y ranuras,
/// y coordina las operaciones de inventario y generación de informes.
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /// @brief Constructor de MainWindow.
    /// @param parent Widget padre en la jerarquía de Qt (por defecto nullptr).
    MainWindow(QWidget *parent = nullptr);

    /// @brief Destructor de MainWindow.
    ~MainWindow();

private slots:
    /// @brief Slot que se ejecuta cuando cambia el texto del campo de búsqueda.
    /// @param text Texto actual ingresado en el QLineEdit de búsqueda.
    void on_searchLineEdit_textChanged(const QString &text);

    /// @brief Slot que se ejecuta al pulsar el botón de agregar componente.
    void on_addButton_clicked();

    /// @brief Slot que se ejecuta al pulsar el botón de editar componente.
    void on_editButton_clicked();

    /// @brief Slot que se ejecuta al pulsar el botón de eliminar componente.
    void on_deleteButton_clicked();

    /// @brief Slot que se ejecuta al pulsar el botón de verificar bajo stock.
    void on_checkLowStockButton_clicked();

    /// @brief Slot que se ejecuta al pulsar el botón de exportar informe CSV.
    void on_exportCSVButton_clicked();

    /// @brief Slot que se ejecuta al pulsar el botón de exportar informe PDF.
    void on_exportPDFButton_clicked();

    /// @brief Actualiza la tabla de componentes en la UI.
    /// @param components Vector de objetos Component que se mostrarán.
    void refreshTable(const std::vector<Component> &components);

private:
    Ui::MainWindow *ui;                 ///< Puntero a la interfaz generada por Qt Designer.
    InventoryManager m_inventory;       ///< Gestor de las operaciones de inventario.
    ReportGenerator m_reporter;         ///< Generador de informes CSV y PDF.
    QStandardItemModel *m_model;        ///< Modelo de datos para la vista de tabla.

    /// @brief Configura el modelo de datos para la tabla de componentes.
    void setupModel();

    /// @brief Carga los datos de la base de datos en la tabla de la UI.
    void loadTable();
};

#endif // MAINWINDOW_H

