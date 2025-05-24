/// @file Component.cpp
/// @brief Implementación de los métodos de la clase Component.

#include "Component.h"

/// @brief Constructor que inicializa un objeto Component con los valores dados.
/// @param id Identificador del componente.
/// @param name Nombre del componente.
/// @param type Tipo o categoría del componente.
/// @param quantity Cantidad inicial disponible del componente.
/// @param location Ubicación física o lógica del componente.
/// @param purchaseDate Fecha en que se realizó la compra del componente.
Component::Component(int id, const QString &name, const QString &type, int quantity,
                     const QString &location, const QDate &purchaseDate)
    : m_id(id)
    , m_name(name)
    , m_type(type)
    , m_quantity(quantity)
    , m_location(location)
    , m_purchaseDate(purchaseDate)
{}

/// @brief Devuelve el identificador del componente.
/// @return Entero que representa el ID del componente.
int Component::id() const
{
    return m_id;
}

/// @brief Devuelve el nombre del componente.
/// @return Cadena con el nombre del componente.
QString Component::name() const
{
    return m_name;
}

/// @brief Devuelve el tipo o categoría del componente.
/// @return Cadena con el tipo del componente.
QString Component::type() const
{
    return m_type;
}

/// @brief Devuelve la cantidad disponible del componente.
/// @return Entero con la cantidad actual.
int Component::quantity() const
{
    return m_quantity;
}

/// @brief Devuelve la ubicación del componente.
/// @return Cadena con la ubicación.
QString Component::location() const
{
    return m_location;
}

/// @brief Devuelve la fecha de compra del componente.
/// @return Objeto QDate con la fecha de compra.
QDate Component::purchaseDate() const
{
    return m_purchaseDate;
}

/// @brief Asigna un nuevo identificador al componente.
/// @param id Nuevo ID a establecer.
void Component::setId(int id)
{
    m_id = id;
}

/// @brief Asigna un nuevo nombre al componente.
/// @param name Nueva cadena para el nombre.
void Component::setName(const QString &name)
{
    m_name = name;
}

/// @brief Asigna un nuevo tipo o categoría al componente.
/// @param type Nueva cadena para el tipo.
void Component::setType(const QString &type)
{
    m_type = type;
}

/// @brief Asigna una nueva cantidad disponible al componente.
/// @param quantity Nuevo valor de cantidad.
void Component::setQuantity(int quantity)
{
    m_quantity = quantity;
}

/// @brief Asigna una nueva ubicación al componente.
/// @param location Nueva cadena para la ubicación.
void Component::setLocation(const QString &location)
{
    m_location = location;
}

/// @brief Asigna una nueva fecha de compra al componente.
/// @param date Nuevo QDate que representa la fecha de compra.
void Component::setPurchaseDate(const QDate &date)
{
    m_purchaseDate = date;
}
