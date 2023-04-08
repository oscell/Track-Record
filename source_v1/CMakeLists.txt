cmake_minimum_required (VERSION 3.15)
project( test )

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
find_library(BCM2835_LIB bcm2835)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(track source.cpp)
target_link_libraries(track ${OpenCV_LIBS} ${BCM2835_LIB})
