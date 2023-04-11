cmake_minimum_required(VERSION 3.15) # Use the highest required version

# GUI project
list(APPEND CMAKE_PREFIX_PATH "/home/oscar/Qt/6.4.3/gcc_64")
project(GUI1_0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GUI1_0
        MANUAL_FINALIZATION
        ${GUI_PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(GUI1_0 SHARED
            ${GUI_PROJECT_SOURCES}
        )
    else()
        add_executable(GUI1_0
            ${GUI_PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GUI1_0 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

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

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GUI1_0)
endif()

# DetectFace project
project(DetectFace)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(facedet src/demo.cpp)
add_executable(client src/client.cpp)

target_link_libraries(client Threads::Threads)
target_link_libraries(facedet ${OpenCV_LIBS})

