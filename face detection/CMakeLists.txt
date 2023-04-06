cmake_minimum_required (VERSION 3.15)
project( DetectFace )

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(facedet src/demo.cpp)
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

target_link_libraries(server Threads::Threads)
target_link_libraries(client Threads::Threads)
target_link_libraries(facedet ${OpenCV_LIBS})
