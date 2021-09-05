cmake_minimum_required(VERSION 3.17)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

link_libraries(hiredis)
add_executable(untitled1 main.cpp test.cpp test.h conredis.cpp conredis)

