/// @file MainWindow.cpp
/// @brief Implementación de la clase MainWindow para la interfaz principal de la aplicación.
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

/// @brief Constructor de MainWindow.
///        Inicializa la interfaz, abre la base de datos, configura el modelo y carga la tabla.
/// @param parent Widget padre en la jerarquía de Qt (por defecto nullptr).
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    // Inicializar base de datos
    const QString dbPath = "inventory.db"; ///< Ruta al archivo de la base de datos
    if (!m_inventory.initialize(dbPath)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos.");
        exit(EXIT_FAILURE);
    }
    setupModel();
    loadTable();
}

/// @brief Destructor de MainWindow.
///        Libera la interfaz de usuario.
MainWindow::~MainWindow()
{
    delete ui;
}

/// @brief Configura el modelo de datos para la tabla de componentes en la UI.
///        Define los encabezados y las propiedades de selección y edición.
void MainWindow::setupModel()
{
    QStringList headers = {"ID", "Nombre", "Tipo", "Cantidad", "Ubicacion", "Fecha Compra"};
    m_model->setHorizontalHeaderLabels(headers);
    ui->componentsTableView->setModel(m_model);
    ui->componentsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->componentsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/// @brief Carga todos los componentes desde la base de datos y los muestra en la tabla.
void MainWindow::loadTable()
{
    m_model->removeRows(0, m_model->rowCount());
    auto components = m_inventory.getAllComponents();
    refreshTable(components);
}

/// @brief Rellena la tabla con la lista de componentes proporcionada.
/// @param components Vector de objetos Component a mostrar.
void MainWindow::refreshTable(const std::vector<Component> &components)
{
    m_model->removeRows(0, m_model->rowCount());
    for (const auto &c : components) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(c.id()));
        row << new QStandardItem(c.name());
        row << new QStandardItem(c.type());
        row << new QStandardItem(QString::number(c.quantity()));
        row << new QStandardItem(c.location());
        row << new QStandardItem(c.purchaseDate().toString(Qt::ISODate));
        m_model->appendRow(row);
    }
}

/// @brief Slot que actualiza la tabla según el texto ingresado en el campo de búsqueda.
/// @param text Texto actual del QLineEdit de búsqueda.
void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        loadTable();
    } else {
        auto results = m_inventory.searchComponents(text);
        refreshTable(results);
    }
}

/// @brief Slot que solicita datos al usuario y agrega un nuevo componente al inventario.
void MainWindow::on_addButton_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Nombre", "Nombre:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    QString type = QInputDialog::getText(this, "Tipo", "Tipo:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    int quantity = QInputDialog::getInt(this, "Cantidad", "Cantidad:", 1, 0, 10000, 1, &ok);
    if (!ok) return;
    QString location = QInputDialog::getText(this, "Ubicacion", "Ubicacion:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    // Solicitar fecha de compra en formato ISO; si está vacía, usar la fecha actual
    QString dateText = QInputDialog::getText(this, "Fecha Compra", "YYYY-MM-DD:",
                                             QLineEdit::Normal, QDate::currentDate().toString(Qt::ISODate), &ok);
    if (!ok) return;
    QDate date = dateText.isEmpty()
                  ? QDate::currentDate()
                  : QDate::fromString(dateText, Qt::ISODate);

    Component c(-1, name, type, quantity, location, date);
    if (m_inventory.addComponent(c)) {
        loadTable();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo agregar el componente.");
    }
}

/// @brief Slot que edita el componente seleccionado solicitando nuevos valores al usuario.
void MainWindow::on_editButton_clicked()
{
    auto index = ui->componentsTableView->currentIndex();
    if (!index.isValid()) return;

    int row = index.row();
    int id = m_model->item(row, 0)->text().toInt();

    QString name = QInputDialog::getText(this, "Nombre", "Nuevo nombre:",
                                         QLineEdit::Normal, m_model->item(row, 1)->text(), nullptr);
    QString type = QInputDialog::getText(this, "Tipo", "Nuevo tipo:",
                                         QLineEdit::Normal, m_model->item(row, 2)->text(), nullptr);
    int quantity = QInputDialog::getInt(this, "Cantidad", "Nueva cantidad:",
                                        m_model->item(row, 3)->text().toInt(), 0, 10000, 1, nullptr);
    QString location = QInputDialog::getText(this, "Ubicacion", "Nueva ubicacion:",
                                             QLineEdit::Normal, m_model->item(row, 4)->text(), nullptr);
    QDate date = QDate::fromString(m_model->item(row, 5)->text(), Qt::ISODate);

    Component c(id, name, type, quantity, location, date);
    if (m_inventory.updateComponent(c)) {
        loadTable();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo actualizar el componente.");
    }
}

/// @brief Slot que elimina el componente seleccionado tras confirmar con el usuario.
void MainWindow::on_deleteButton_clicked()
{
    auto index = ui->componentsTableView->currentIndex();
    if (!index.isValid()) return;

    int id = m_model->item(index.row(), 0)->text().toInt();
    if (QMessageBox::question(this, "Eliminar", "¿Eliminar este componente?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        if (m_inventory.removeComponent(id)) {
            loadTable();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo eliminar el componente.");
        }
    }
}

/// @brief Slot que filtra y muestra los componentes con stock por debajo del umbral indicado.
void MainWindow::on_checkLowStockButton_clicked()
{
    int threshold = ui->lowStockSpinBox->value();
    auto low = m_inventory.getLowStockComponents(threshold);
    refreshTable(low);
}

/// @brief Slot que exporta todos los componentes a un archivo CSV seleccionado por el usuario.
void MainWindow::on_exportCSVButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar CSV", "", "CSV Files (*.csv)");
    if (filePath.isEmpty()) return;

    auto all = m_inventory.getAllComponents();
    if (!m_reporter.generateCSV(filePath, all)) {
        QMessageBox::warning(this, "Error", "No se pudo generar el CSV.");
    }
}

/// @brief Slot que exporta todos los componentes a un archivo PDF seleccionado por el usuario.
void MainWindow::on_exportPDFButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) return;

    auto all = m_inventory.getAllComponents();
    if (!m_reporter.generatePDF(filePath, all)) {
        QMessageBox::warning(this, "Error", "No se pudo generar el PDF.");
    }
}

