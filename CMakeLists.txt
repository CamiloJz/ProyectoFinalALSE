cmake_minimum_required(VERSION 3.5)

# 1. Nombre del proyecto y estandar C++
project(GestorInventario LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Habilitar AUTOMOC, AUTOUIC y AUTORCC para Qt
#    - AUTOMOC: genera automáticamente los moc_*.cpp a partir de clases con Q_OBJECT 
#    - AUTOUIC: permite procesar .ui sin qt5_wrap_ui explícito 
#    - AUTORCC: procesa .qrc sin qt5_add_resources explícito 
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 3. Buscar las librerías de Qt5 que necesitamos
find_package(Qt5 REQUIRED COMPONENTS Widgets Sql PrintSupport)

# 4. Incluir el directorio de compilación para que encuentre los archivos generados (ui_*.h, moc_*.cpp, qrc_*.cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# 5. Listado de todos los .cpp del proyecto
set(SOURCES
    main.cpp
    MainWindow.cpp
    Component.cpp
    DatabaseManager.cpp
    InventoryManager.cpp
    ReportGenerator.cpp
)

# 6. Listado de todos los .h (no es estrictamente necesario listarlos aquí,
#    pero ayuda a organizar el proyecto y facilita que tu IDE los identifique)
set(HEADERS
    MainWindow.h
    Component.h
    DatabaseManager.h
    InventoryManager.h
    ReportGenerator.h
)

# 7. Listado de los archivos .ui (Qt Designer)
set(UI_FILES
    MainWindow.ui
)

# 8. Listado de los recursos (.qrc) — si de momento no vas a usar iconos, puedes dejarlo vacío
set(RC_FILES
    resources.qrc
)

# 9. Crear el ejecutable, incluyendo:
#    - Fuentes (.cpp)
#    - Cabeceras (.h)
#    - Interfaces Qt (.ui) <-- AUTOUIC se encargará de procesarlos
#    - Recursos Qt (.qrc)   <-- AUTORCC los procesará
add_executable(GestorInventario
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RC_FILES}
)

# 10. Enlazar con los módulos Qt necesarios
target_link_libraries(GestorInventario
    Qt5::Widgets
    Qt5::Sql
    Qt5::PrintSupport
)

# 11. (Opcional) Si quieres que el binario se llame exactamente “GestorInventario” sin sufijos:
set_target_properties(GestorInventario PROPERTIES OUTPUT_NAME "GestorInventario")
