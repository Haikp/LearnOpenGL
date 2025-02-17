#currently does nothing
cmake_minimum_required(VERSION 3.20)
project(OpenGLLearning VERSION 0.1.0)

add_executable(app src/main.cpp)

set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src
)

set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glfw3/glfw3Config.cmake" ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glew/glew-config.cmake" ${CMAKE_PREFIX_PATH})
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(00_Template)
add_subdirectory(01_BufferAndObjects)
