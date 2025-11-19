cmake_minimum_required(VERSION 3.5)


project(JuegoNapoleonN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

qt_standard_project_setup()

qt_add_executable(appJuegoNapoleonN
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    pantallanivel1.h pantallanivel1.cpp pantallanivel1.ui
    pantallanivel2.h pantallanivel2.cpp pantallanivel2.ui
    pantallanivel3.h pantallanivel3.cpp pantallanivel3.ui
    movimientoparticula.h movimientoparticula.cpp
    cannonball.h cannonball.cpp
)

target_link_libraries(appJuegoNapoleonN PRIVATE
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)

set_target_properties(appJuegoNapoleonN PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

install(TARGETS appJuegoNapoleonN
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
