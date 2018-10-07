cmake_minimum_required(VERSION 3.12)
project(jpeg_encoder_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(jpeg_encoder_master
        jpeg_encoder.cpp
        jpeg_encoder.h
        test.cpp)
