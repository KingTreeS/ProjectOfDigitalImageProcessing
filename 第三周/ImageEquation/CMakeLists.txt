cmake_minimum_required(VERSION 3.12)
project(ImageEquation)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ImageEquation src/main.cpp)
target_link_libraries(ImageEquation ${OpenCV_LIBS})