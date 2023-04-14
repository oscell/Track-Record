cmake_minimum_required (VERSION 3.15)
project( tracknrecord )


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

find_library(BCM2835_LIB bcm2835)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(tracknrecord src/source.cpp)
add_executable(server src/server.cpp)

target_link_libraries(server Threads::Threads)
target_link_libraries(tracknrecord ${OpenCV_LIBS} ${BCM2835_LIB})
