cmake_minimum_required(VERSION 3.25.0)
project(test)

set(CMAKE_CXX_STANDARD 17)

add_executable(test
        Source.cpp
)
FILE(COPY "data/main.txt" DESTINATION "data/")
FILE(COPY "data/out.txt" DESTINATION "data/")
FILE(COPY "data/temp/0" DESTINATION "data/temp")
FILE(COPY "data/temp/1" DESTINATION "data/temp")
FILE(COPY "data/temp/2" DESTINATION "data/temp")
FILE(COPY "data/temp/3" DESTINATION "data/temp")