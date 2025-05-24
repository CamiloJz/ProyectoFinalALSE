/// @file ReportGenerator.h
/// @brief Declaración de la clase ReportGenerator para generar informes de componentes.
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QObject>
#include <QString>
#include <vector>
#include "Component.h"

/// @class ReportGenerator
/// @brief Clase responsable de generar informes en distintos formatos a partir de una lista de componentes.
///
/// Esta clase proporciona métodos para exportar la información de los componentes
/// a archivos CSV y PDF, permitiendo su visualización y análisis externos.
class ReportGenerator : public QObject {
    Q_OBJECT

public:
    /// @brief Constructor de ReportGenerator.
    /// @param parent Objeto padre en la jerarquía de Qt (por defecto nullptr).
    explicit ReportGenerator(QObject *parent = nullptr);

    /// @brief Destructor de ReportGenerator.
    ~ReportGenerator();

    /// @brief Genera un informe en formato CSV con la lista de componentes proporcionada.
    /// @param filePath Ruta (incluyendo nombre y extensión) donde se guardará el archivo CSV.
    /// @param components Vector de objetos Component que se incluirán en el informe.
    /// @return true si el archivo CSV se genera y guarda correctamente; false en caso de error.
    bool generateCSV(const QString &filePath, const std::vector<Component> &components);

    /// @brief Genera un informe en formato PDF con la lista de componentes proporcionada.
    /// @param filePath Ruta (incluyendo nombre y extensión) donde se guardará el archivo PDF.
    /// @param components Vector de objetos Component que se incluirán en el informe.
    /// @return true si el archivo PDF se genera y guarda correctamente; false en caso de error.
    bool generatePDF(const QString &filePath, const std::vector<Component> &components);
};

#endif // REPORTGENERATOR_H

