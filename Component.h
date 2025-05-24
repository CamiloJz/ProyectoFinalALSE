/**
 * @file Component.h
 * @brief Define la clase Component, que representa un componente de inventario
 *        con propiedades como id, nombre, tipo, cantidad, ubicación y fecha de compra.
 */
#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QDate>

/**
 * @class Component
 * @brief Representa un componente de inventario con atributos identificadores y descriptivos.
 *
 * La clase Component encapsula los detalles de un único artículo de inventario,
 * incluidos un identificador único, nombre descriptivo, tipo, cantidad disponible,
 * ubicación de almacenamiento y fecha de compra.
 */
class Component {
public:
    /**
     * @brief Construye un Component con valores iniciales opcionales.
     * @param id Identificador único del componente (por defecto: -1).
     * @param name Nombre descriptivo del componente (por defecto: cadena vacía).
     * @param type Tipo o categoría del componente (por defecto: cadena vacía).
     * @param quantity Cantidad de unidades disponibles (por defecto: 0).
     * @param location Ubicación de almacenamiento (por defecto: cadena vacía).
     * @param purchaseDate Fecha de compra del componente (por defecto: fecha actual).
     */
    Component(int id = -1,
              const QString &name = "",
              const QString &type = "",
              int quantity = 0,
              const QString &location = "",
              const QDate &purchaseDate = QDate::currentDate());

    // Getters
    /**
     * @brief Obtiene el identificador único del componente.
     * @return El id del componente como entero.
     */
    int id() const;

    /**
     * @brief Obtiene el nombre descriptivo del componente.
     * @return El nombre del componente como QString.
     */
    QString name() const;

    /**
     * @brief Obtiene el tipo o categoría del componente.
     * @return El tipo del componente como QString.
     */
    QString type() const;

    /**
     * @brief Obtiene la cantidad disponible del componente.
     * @return El número de unidades disponibles como entero.
     */
    int quantity() const;

    /**
     * @brief Obtiene la ubicación de almacenamiento del componente.
     * @return La ubicación del componente como QString.
     */
    QString location() const;

    /**
     * @brief Obtiene la fecha de compra del componente.
     * @return La fecha de compra como QDate.
     */
    QDate purchaseDate() const;

    // Setters
    /**
     * @brief Establece el identificador único del componente.
     * @param id Nuevo valor de id.
     */
    void setId(int id);

    /**
     * @brief Establece el nombre descriptivo del componente.
     * @param name Nuevo valor de nombre.
     */
    void setName(const QString &name);

    /**
     * @brief Establece el tipo o categoría del componente.
     * @param type Nuevo valor de tipo.
     */
    void setType(const QString &type);

    /**
     * @brief Establece la cantidad disponible del componente.
     * @param quantity Nuevo valor de cantidad.
     */
    void setQuantity(int quantity);

    /**
     * @brief Establece la ubicación de almacenamiento del componente.
     * @param location Nuevo valor de ubicación.
     */
    void setLocation(const QString &location);

    /**
     * @brief Establece la fecha de compra del componente.
     * @param date Nueva fecha de compra como QDate.
     */
    void setPurchaseDate(const QDate &date);

private:
    int m_id;            /**< Identificador único del componente */
    QString m_name;      /**< Nombre descriptivo del componente */
    QString m_type;      /**< Tipo o categoría del componente */
    int m_quantity;      /**< Número de unidades disponibles */
    QString m_location;  /**< Ubicación de almacenamiento */
    QDate m_purchaseDate;/**< Fecha de compra del componente */
};
#endif // COMPONENT_H

