cmake_minimum_required(VERSION 3.12)
project(ImageZoom)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ImageZoom src/main.cpp)
target_link_libraries(ImageZoom ${OpenCV_LIBS})