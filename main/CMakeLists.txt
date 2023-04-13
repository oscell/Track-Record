cmake_minimum_required (VERSION 3.15)
project( tracknrecord )


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(GUI_PROJECT_SOURCES
        src/GUI/main.cpp
        src/GUI/mainwindow.cpp
        src/GUI/mainwindow.h
        src/GUI/mainwindow.ui
)



find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

find_library(BCM2835_LIB bcm2835)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(tracknrecord src/source.cpp)
add_executable(client src/client.cpp)

target_link_libraries(client Threads::Threads)
target_link_libraries(tracknrecord ${OpenCV_LIBS} ${BCM2835_LIB})
