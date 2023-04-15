cmake_minimum_required(VERSION 3.15)
project(tracknrecord)

# GUI project
project(GUI1_0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Qt5_DIR "/home/oscar/Qt/Tools/QtDesignStudio/qt5_design_studio_reduced_version/lib/cmake/Qt5")

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(OpenCV REQUIRED)

set(GUI_PROJECT_SOURCES
        src/GUI/main.cpp
        src/GUI/mainwindow.cpp
        src/GUI/mainwindow.h
        src/GUI/mainwindow.ui
)

add_executable(GUI1_0
    ${GUI_PROJECT_SOURCES}
)

target_link_libraries(GUI1_0 PRIVATE Qt5::Widgets)
target_link_libraries(GUI1_0 PRIVATE ${OpenCV_LIBS}) # Add this line

set_target_properties(GUI1_0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GUI1_0
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
