/// @file main.cpp
/// @brief Punto de entrada de la aplicación de inventario.
#include "MainWindow.h"
#include <QApplication>

/// @brief Función principal de la aplicación.
///        Inicializa QApplication, crea y muestra la ventana principal.
/// @param argc Número de argumentos de línea de comandos.
/// @param argv Vector de cadenas con cada argumento de línea de comandos.
/// @return Resultado de la ejecución de la aplicación (0 si finaliza correctamente).
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);  ///< Objeto de aplicación Qt.
    MainWindow w;                ///< Ventana principal de la aplicación.
    w.show();                    ///< Muestra la ventana principal.
    return a.exec();             ///< Entra en el bucle de eventos Qt.
}

