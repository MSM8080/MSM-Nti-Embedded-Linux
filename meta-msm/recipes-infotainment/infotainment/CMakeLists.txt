cmake_minimum_required(VERSION 3.16)

project(msm_project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)


qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appmsm_project
    main.cpp
)

qt_add_qml_module(appmsm_project
    URI msm_project
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES Chair.qml Fuel.qml Momrec.qml Speedometer.qml Tachometer.qml Themes.qml
        SOURCES csv.cpp csv.h
        SOURCES login.cpp login.h
        SOURCES user.cpp user.h
        SOURCES user_repo.cpp user_repo.h
        SOURCES qt_screen_theme.cpp qt_screen_theme.h
        RESOURCES users_data.txt
        SOURCES app.h app.cpp
        SOURCES qt_screen_sensors.h qt_screen_sensors.cpp
        QML_FILES Sensors.qml
        SOURCES qt_serial_handler.h qt_serial_handler.cpp
        SOURCES ArduinoComm.cpp ArduinoComm.hpp
        RESOURCES login.txt
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appmsm_project PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appmsm_project
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appmsm_project
    PRIVATE Qt6::Quick
            Qt6::SerialPort
)
target_link_libraries(appmsm_project PRIVATE Qt6::Core)
target_link_libraries(appmsm_project PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appmsm_project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
