/// @file DatabaseManager.h
/// @brief Declaración de la clase DatabaseManager para gestionar la conexión y operaciones en la base de datos.

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include "Component.h"
#include <vector>

/// @class DatabaseManager
/// @brief Clase que administra la conexión y las operaciones CRUD sobre la base de datos de componentes.
///
/// Esta clase hereda de QObject para integrarse con el sistema de señales y ranuras de Qt.
/// Permite abrir/cerrar la base de datos, inicializar tablas y realizar operaciones
/// de inserción, actualización, eliminación y consulta de componentes.
class DatabaseManager : public QObject {
    Q_OBJECT
public:
    /// @brief Constructor de DatabaseManager.
    /// @param parent Objeto padre en la jerarquía de Qt (por defecto nullptr).
    explicit DatabaseManager(QObject *parent = nullptr);

    /// @brief Destructor de DatabaseManager.
    /// Cierra la conexión a la base de datos si está abierta.
    ~DatabaseManager();

    /// @brief Abre una conexión a la base de datos SQLite en la ruta especificada.
    /// @param path Ruta al archivo de base de datos.
    /// @return true si la conexión se abre exitosamente; false en caso de error.
    bool openDatabase(const QString &path);

    /// @brief Cierra la conexión a la base de datos.
    void closeDatabase();

    /// @brief Crea las tablas necesarias en la base de datos si no existen.
    /// @return true si la creación (o existencia previa) de las tablas es exitosa; false en caso de error.
    bool initializeTables();

    /// @brief Inserta un nuevo componente en la tabla de componentes.
    /// @param component Objeto Component con los datos a insertar.
    /// @return true si la inserción se realiza correctamente; false en caso de error.
    bool addComponent(const Component &component);

    /// @brief Actualiza los datos de un componente existente.
    /// @param component Objeto Component con el ID y los nuevos valores a actualizar.
    /// @return true si la actualización se realiza correctamente; false en caso de error.
    bool updateComponent(const Component &component);

    /// @brief Elimina un componente de la base de datos según su ID.
    /// @param id Identificador del componente a eliminar.
    /// @return true si la eliminación es exitosa; false en caso de error.
    bool removeComponent(int id);

    /// @brief Recupera todos los componentes almacenados en la base de datos.
    /// @return Vector de objetos Component con todos los registros encontrados.
    std::vector<Component> fetchAllComponents();

    /// @brief Busca componentes cuyo nombre o tipo contenga la palabra clave proporcionada.
    /// @param keyword Cadena utilizada como filtro de búsqueda.
    /// @return Vector de objetos Component que coinciden con la búsqueda.
    std::vector<Component> searchComponents(const QString &keyword);

private:
    QSqlDatabase m_db;  ///< Objeto que representa la conexión a la base de datos SQLite.
};

#endif // DATABASEMANAGER_H


