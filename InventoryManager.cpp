/// @file InventoryManager.cpp
/// @brief Implementación de los métodos de la clase InventoryManager para la gestión de inventario.

#include "InventoryManager.h"
#include <algorithm>

/// @brief Constructor de InventoryManager.
/// @param parent Objeto padre en la jerarquía de Qt (por defecto nullptr).
InventoryManager::InventoryManager(QObject *parent)
    : QObject(parent)
{}
/// @brief Destructor de InventoryManager.
/// Libera recursos si es necesario.
InventoryManager::~InventoryManager()
{}

/// @brief Inicializa el gestor de inventario abriendo la base de datos y creando las tablas.
/// @param dbPath Ruta al archivo de la base de datos SQLite.
/// @return true si la base de datos se abre y las tablas se inicializan correctamente; false en caso de error.
bool InventoryManager::initialize(const QString &dbPath) {
    if (!m_dbManager.openDatabase(dbPath))
        return false;
    return m_dbManager.initializeTables();
}

/// @brief Obtiene todos los componentes del inventario.
/// @return Vector con todos los objetos Component almacenados en la base de datos.
std::vector<Component> InventoryManager::getAllComponents() {
    return m_dbManager.fetchAllComponents();
}

/// @brief Busca componentes cuyo nombre, tipo o ubicación contenga la palabra clave.
/// @param keyword Cadena utilizada como filtro de búsqueda.
/// @return Vector con los componentes que coinciden con el criterio proporcionado.
std::vector<Component> InventoryManager::searchComponents(const QString &keyword) {
    return m_dbManager.searchComponents(keyword);
}

/// @brief Agrega un nuevo componente al inventario.
/// @param component Objeto Component con los datos del nuevo componente.
/// @return true si la inserción se realiza correctamente; false en caso de error.
bool InventoryManager::addComponent(const Component &component) {
    return m_dbManager.addComponent(component);
}

/// @brief Actualiza un componente existente en el inventario.
/// @param component Objeto Component con el ID y los nuevos datos a actualizar.
/// @return true si la actualización se efectúa correctamente; false en caso de error.
bool InventoryManager::updateComponent(const Component &component) {
    return m_dbManager.updateComponent(component);
}

/// @brief Elimina un componente del inventario según su ID.
/// @param id Identificador del componente a eliminar.
/// @return true si la eliminación se realiza correctamente; false en caso de error.
bool InventoryManager::removeComponent(int id) {
    return m_dbManager.removeComponent(id);
}

/// @brief Obtiene los componentes cuyo stock está por debajo o igual a un umbral.
/// @param threshold Cantidad máxima para considerar un componente con bajo stock.
/// @return Vector con los componentes con cantidad menor o igual al umbral.
std::vector<Component> InventoryManager::getLowStockComponents(int threshold) {
    std::vector<Component> all = m_dbManager.fetchAllComponents();
    std::vector<Component> low;
    std::copy_if(all.begin(), all.end(), std::back_inserter(low),
                 [threshold](const Component &c) { return c.quantity() <= threshold; });
    return low;
}

