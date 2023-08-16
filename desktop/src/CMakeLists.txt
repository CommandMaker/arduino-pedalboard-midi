project(application)

find_package(Qt6 REQUIRED COMPONENTS Widgets SerialPort)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set(QT_RESOURCES resources/resources.qrc)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

qt_add_executable(application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QT_RESOURCES}
)

target_link_libraries(application PRIVATE Qt6::Widgets Qt6::SerialPort)

include(GNUInstallDirs)
install(TARGETS application
        BUNDLE DESTINATION application
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(application)
endif()
