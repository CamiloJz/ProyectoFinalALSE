/// @file DatabaseManager.cpp
/// @brief Implementación de los métodos de la clase DatabaseManager para gestionar la base de datos.

#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

/// @brief Constructor de DatabaseManager.
/// @param parent Objeto padre en la jerarquía de Qt (por defecto nullptr).
DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{}

/// @brief Destructor de DatabaseManager.
/// Cierra la conexión a la base de datos si aún está abierta.
DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

/// @brief Abre (o reutiliza) la conexión a la base de datos SQLite.
/// @param path Ruta al archivo de la base de datos.
/// @return true si la conexión se establece correctamente; false en caso de error.
bool DatabaseManager::openDatabase(const QString &path)
{
    if (QSqlDatabase::contains("qt_inventory_connection")) {
        m_db = QSqlDatabase::database("qt_inventory_connection");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "qt_inventory_connection");
        m_db.setDatabaseName(path);
    }

    if (!m_db.open()) {
        qDebug() << "Error al abrir DB:" << m_db.lastError().text();
        return false;
    }
    return true;
}

/// @brief Cierra la conexión a la base de datos si está abierta.
void DatabaseManager::closeDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}
/// @brief Crea las tablas necesarias en la base de datos si no existen.
/// @return true si la tabla se crea o ya existía sin errores; false en caso contrario.
bool DatabaseManager::initializeTables()
{
    QSqlQuery query(m_db);
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS components (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            type TEXT,
            quantity INTEGER NOT NULL,
            location TEXT,
            purchase_date TEXT
        )
    )";
    if (!query.exec(createTable)) {
        qDebug() << "Error al crear tabla:" << query.lastError().text();
        return false;
    }
    return true;
}

/// @brief Inserta un nuevo componente en la tabla `components`.
/// @param component Objeto Component con los datos a almacenar.
/// @return true si la inserción se realiza correctamente; false en caso de error.
bool DatabaseManager::addComponent(const Component &component)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        INSERT INTO components (name, type, quantity, location, purchase_date)
        VALUES (:name, :type, :quantity, :location, :purchase_date)
    )");
    query.bindValue(":name", component.name());
    query.bindValue(":type", component.type());
    query.bindValue(":quantity", component.quantity());
    query.bindValue(":location", component.location());
    query.bindValue(":purchase_date", component.purchaseDate().toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "Error al insertar componente:" << query.lastError().text();
        return false;
    }
    return true;
}

/// @brief Actualiza los datos de un componente existente en la tabla.
/// @param component Objeto Component con el ID y los nuevos valores.
/// @return true si la actualización se realiza correctamente; false en caso de error.
bool DatabaseManager::updateComponent(const Component &component)
{
    QSqlQuery query(m_db);
    query.prepare(R"(
        UPDATE components
        SET name = :name,
            type = :type,
            quantity = :quantity,
            location = :location,
            purchase_date = :purchase_date
        WHERE id = :id
    )");
    query.bindValue(":id", component.id());
    query.bindValue(":name", component.name());
    query.bindValue(":type", component.type());
    query.bindValue(":quantity", component.quantity());
    query.bindValue(":location", component.location());
    query.bindValue(":purchase_date", component.purchaseDate().toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "Error al actualizar componente:" << query.lastError().text();
        return false;
    }
    return true;
}

/// @brief Elimina un componente de la tabla según su ID.
/// @param id Identificador del componente a eliminar.
/// @return true si la eliminación se efectúa correctamente; false en caso de error.
bool DatabaseManager::removeComponent(int id)
{
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM components WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Error al eliminar componente:" << query.lastError().text();
        return false;
    }
    return true;
}

/// @brief Recupera todos los componentes almacenados en la base de datos.
/// @return Vector de Component con todos los registros obtenidos; vector vacío en caso de error.
std::vector<Component> DatabaseManager::fetchAllComponents()
{
    std::vector<Component> list;
    QSqlQuery query(m_db);
    if (!query.exec("SELECT id, name, type, quantity, location, purchase_date FROM components")) {
        qDebug() << "Error al obtener componentes:" << query.lastError().text();
        return list;
    }
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString type = query.value(2).toString();
        int quantity = query.value(3).toInt();
        QString location = query.value(4).toString();
        QDate date = QDate::fromString(query.value(5).toString(), Qt::ISODate);
        list.emplace_back(id, name, type, quantity, location, date);
    }
    return list;
}

/// @brief Busca componentes cuyo nombre, tipo o ubicación coincida con la palabra clave.
/// @param keyword Cadena utilizada para el filtro de búsqueda (se envuelve en '%').
/// @return Vector de Component que coinciden con la búsqueda; vector vacío en caso de error.
std::vector<Component> DatabaseManager::searchComponents(const QString &keyword)
{
    std::vector<Component> list;
    QSqlQuery query(m_db);
    query.prepare(R"(
        SELECT id, name, type, quantity, location, purchase_date
        FROM components
        WHERE name LIKE :kw OR type LIKE :kw OR location LIKE :kw
    )");
    QString pattern = "%" + keyword + "%";
    query.bindValue(":kw", pattern);
    if (!query.exec()) {
        qDebug() << "Error en búsqueda:" << query.lastError().text();
        return list;
    }
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString type = query.value(2).toString();
        int quantity = query.value(3).toInt();
        QString location = query.value(4).toString();
        QDate date = QDate::fromString(query.value(5).toString(), Qt::ISODate);
        list.emplace_back(id, name, type, quantity, location, date);
    }
    return list;
}


