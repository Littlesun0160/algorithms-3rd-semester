cmake_minimum_required(VERSION 3.25.0)
project(lab_14)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_14 main.cpp)

FILE(COPY "data/input.txt" DESTINATION "data/")
FILE(COPY "data/out.txt" DESTINATION "data/")