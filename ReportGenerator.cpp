/// @file ReportGenerator.cpp
/// @brief Implementación de los métodos de la clase ReportGenerator para generación de informes en CSV y PDF.

#include "ReportGenerator.h"
#include <QFile>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <QPdfWriter>
#include <QPainter>

/// @brief Constructor de ReportGenerator.
/// @param parent Objeto padre en la jerarquía de Qt (por defecto nullptr).
ReportGenerator::ReportGenerator(QObject *parent)
    : QObject(parent)
{}

/// @brief Destructor de ReportGenerator.
ReportGenerator::~ReportGenerator()
{}

/// @brief Genera un informe en formato CSV con la lista de componentes proporcionada.
/// @param filePath Ruta completa (incluyendo nombre y extensión) donde se guardará el archivo CSV.
/// @param components Vector de objetos Component que se incluirán en el informe.
/// @return true si el archivo CSV se abre y escribe correctamente; false en caso de fallo al abrir o escribir.
bool ReportGenerator::generateCSV(const QString &filePath, const std::vector<Component> &components) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    // Cabecera del CSV
    out << "ID,Nombre,Tipo,Cantidad,Ubicacion,FechaCompra\n";
    // Filas con los datos de cada componente
    for (const auto &c : components) {
        out << c.id() << ","
            << c.name() << ","
            << c.type() << ","
            << c.quantity() << ","
            << c.location() << ","
            << c.purchaseDate().toString(Qt::ISODate) << "\n";
    }
    file.close();
    return true;
}

/// @brief Genera un informe en formato PDF con la lista de componentes proporcionada.
/// @param filePath Ruta completa (incluyendo nombre y extensión) donde se guardará el archivo PDF.
/// @param components Vector de objetos Component que se incluirán en el informe.
/// @return true si el PDF se genera y guarda correctamente; false en caso de error durante la generación.
bool ReportGenerator::generatePDF(const QString &filePath, const std::vector<Component> &components) {
QPdfWriter writer(filePath);
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setResolution(300);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    // Título
    cursor.insertText("Reporte de Inventario - " + QDate::currentDate().toString(Qt::ISODate) + "\n\n");

    // Tabla
    QTextTableFormat tableFormat;
    tableFormat.setHeaderRowCount(1);
    tableFormat.setCellPadding(4);
    tableFormat.setCellSpacing(0);
    tableFormat.setBorder(1);

    QTextTable *table = cursor.insertTable(components.size() + 1, 6, tableFormat);

    // Cabeceras
    QStringList headers = {"ID", "Nombre", "Tipo", "Cantidad", "Ubicación", "Fecha Compra"};
    for (const QString &header : headers) {
        cursor.insertText(header);
        cursor.movePosition(QTextCursor::NextCell);
    }

    // Datos
    for (const auto &c : components) {
        cursor.insertText(QString::number(c.id()));
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(c.name());
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(c.type());
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(QString::number(c.quantity()));
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(c.location());
        cursor.movePosition(QTextCursor::NextCell);
        cursor.insertText(c.purchaseDate().toString(Qt::ISODate));
        cursor.movePosition(QTextCursor::NextCell);
    }

    doc.setPageSize(QSizeF(writer.width(), writer.height()));
    doc.print(&writer);

    return true;
}
