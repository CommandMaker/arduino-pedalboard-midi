project(application)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets SerialPort)

set(QT_RESOURCES resources/resources.qrc)

set(PROJECT_SOURCES
        main.cpp
        ui/MainWindow.cpp
        ui/MainWindow.h
        ui/MainWindow.ui
        JSONManipulator.cpp
        JSONManipulator.h
        communication/SerialCommunication.cpp
        communication/SerialCommunication.h
        communication/MIDICommunication.cpp
        communication/MIDICommunication.h
        config/AppConfiguration.cpp
        config/AppConfiguration.h
        ui/settings/SettingsDialog.cpp
        ui/settings/SettingsDialog.h
        ui/settings/SettingsDialog.ui
)

if (WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_WIN32_EXECUTABLE ON)
endif ()

qt_add_executable(application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QT_RESOURCES}
)

target_link_libraries(application PRIVATE Qt6::Widgets Qt6::SerialPort rtmidi)

include(GNUInstallDirs)
install(TARGETS application
        BUNDLE DESTINATION application
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(application)
endif()
