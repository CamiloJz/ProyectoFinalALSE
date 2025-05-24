/// @file ReportGenerator.cpp
/// @brief Implementación de los métodos de la clase ReportGenerator para generación de informes en CSV y PDF.

#include "ReportGenerator.h"
#include <QFile>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>

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
    QPainter painter(&writer);

    int y = 100;
    // Título del informe con la fecha actual
    painter.setFont(QFont("Helvetica", 12));
    painter.drawText(100, 50, "Reporte de Inventario - " + QDate::currentDate().toString(Qt::ISODate));
    // Cabecera de columnas
    painter.drawText(100, y, "ID   Nombre   Tipo   Cantidad   Ubicacion   FechaCompra");
    y += 30;

    // Contenido de cada componente
    for (const auto &c : components) {
        QString line = QString::number(c.id()) + "   " + c.name() + "   " + c.type() + "   "
                       + QString::number(c.quantity()) + "   " + c.location() + "   "
                       + c.purchaseDate().toString(Qt::ISODate);
        painter.drawText(100, y, line);
        y += 20;
        // Nueva página si se supera el límite inferior
        if (y > writer.height() - 100) {
            writer.newPage();
            y = 100;
        }
    }
    painter.end();
    return true;
}

