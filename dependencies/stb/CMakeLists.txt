cmake_minimum_required(VERSION 3.20)
project(stb)

add_library(stb STATIC stb.cpp)
#the term interface refers to the library being usable by other projects that have CMakeLists.txt
#in a modular setting, since this "subdirectory" is a library that is potentially in use, we use interface to allow the project to use this particular library
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
