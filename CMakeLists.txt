cmake_minimum_required(VERSION 3.2)
project(main)
include_directories(
    include/
    )
set(HEADERS include/SafeQueue.h include/ThreadPool.h)
set(SOURCES src/ThreadPool.cpp)
SET(CMAKE_CXX_FLAGS -pthread)
add_compile_options(
	-std=c++11
#        -D_DEBUG
#        -g
) 
add_executable(main ${HEADERS} ${SOURCES} main.cpp)