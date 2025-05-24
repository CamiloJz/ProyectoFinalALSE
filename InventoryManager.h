/// @file InventoryManager.h
/// @brief Declaración de la clase InventoryManager para la gestión de inventario.

#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <QObject>
#include <vector>
#include "Component.h"
#include "DatabaseManager.h"

/// @class InventoryManager
/// @brief Clase que actúa como capa intermedia entre la interfaz de usuario y la base de datos.
///
/// Esta clase utiliza DatabaseManager para realizar operaciones de inventario
/// como obtención, búsqueda, adición, actualización, eliminación y detección
/// de componentes con bajo stock.
class InventoryManager : public QObject {
    Q_OBJECT

public:
    /// @brief Constructor de InventoryManager.
    /// @param parent Objeto padre en la jerarquía de Qt (por defecto nullptr).
    explicit InventoryManager(QObject *parent = nullptr);

    /// @brief Destructor de InventoryManager.
    ~InventoryManager();

    /// @brief Inicializa el gestor de inventario abriendo la base de datos.
    /// @param dbPath Ruta al archivo de la base de datos SQLite.
    /// @return true si la inicialización (apertura de la base y creación de tablas) es exitosa; false en caso de error.
    bool initialize(const QString &dbPath);

    /// @brief Obtiene todos los componentes del inventario.
    /// @return Vector con los objetos Component representando cada registro de la base.
    std::vector<Component> getAllComponents();

    /// @brief Busca componentes cuyo nombre, tipo o ubicación contenga la palabra clave.
    /// @param keyword Cadena utilizada para filtrar la búsqueda.
    /// @return Vector con los objetos Component que coinciden con el criterio de búsqueda.
    std::vector<Component> searchComponents(const QString &keyword);

    /// @brief Agrega un nuevo componente al inventario.
    /// @param component Objeto Component con los datos del nuevo componente.
    /// @return true si la operación se completa correctamente; false en caso de error.
    bool addComponent(const Component &component);
    /// @brief Actualiza los datos de un componente existente en el inventario.
    /// @param component Objeto Component con el ID y los nuevos datos.
    /// @return true si la actualización se realiza correctamente; false en caso de error.
    bool updateComponent(const Component &component);

    /// @brief Elimina un componente del inventario según su ID.
    /// @param id Identificador del componente a eliminar.
    /// @return true si la eliminación es exitosa; false en caso de error.
    bool removeComponent(int id);

    /// @brief Obtiene los componentes cuyo stock está por debajo de un umbral.
    /// @param threshold Cantidad mínima aceptable antes de considerarse bajo stock.
    /// @return Vector con los objetos Component que tienen cantidad menor al umbral.
    std::vector<Component> getLowStockComponents(int threshold);

private:
    DatabaseManager m_dbManager;  ///< Gestor de la base de datos subyacente.
};

#endif // INVENTORYMANAGER_H

