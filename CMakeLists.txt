cmake_minimum_required(VERSION 4.1)
project(zad2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(zad2
        src/bnb.cpp
        src/bnb.h
        src/tsp.h
        src/nn.cpp
        src/nn.h
        src/config.cpp
        src/config.h
        src/main.cpp
        src/loader.cpp
        src/loader.h)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")