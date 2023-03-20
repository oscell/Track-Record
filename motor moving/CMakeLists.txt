cmake_minimum_required (VERSION 3.15)
project( MoveMotor )

set(CMAKE_CXX_STANDARD 17)
find_library(BCM2835_LIB bcm2835)
add_executable(move move.cpp)
target_link_libraries(move ${BCM2835_LIB})
