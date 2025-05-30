cmake_minimum_required(VERSION 3.20)
project(test_project VERSION 0.1.0)

add_definitions(-DSHADER_PATH=${CMAKE_SOURCE_DIR}/shaders/)
add_definitions(-DTEXTURE_PATH=${CMAKE_SOURCE_DIR}/textures/)
add_definitions(-DMODEL_PATH=${CMAKE_SOURCE_DIR}/models/)

add_executable(app
    src/main.cpp
    ${CMAKE_SOURCE_DIR}/../dependencies/stb/stb.cpp
)

set(OSBitness 32)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir}
)

include_directories(${CMAKE_SOURCE_DIR}/../include)
#add_subdirectory(${CMAKE_SOURCE_DIR}/../dependencies/stb ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/stb)
#add_subdirectory(${CMAKE_SOURCE_DIR}/../dependencies/glm ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/glm)

add_library(my_library SHARED
    ../src/shaders.cpp
#    ../src/mesh.cpp
    ../src/camera.cpp
#    ../src/bettermesh.cpp
#    ../src/model.cpp
)

set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glfw3/glfw3Config.cmake" ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glew/glew-config.cmake" ${CMAKE_PREFIX_PATH})
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(app PRIVATE glfw3)
target_link_libraries(app PRIVATE glfw3 dl)
target_link_libraries(app PRIVATE glfw3 ${OPENGL_LIBRARIES} pthread)
target_link_libraries(app PRIVATE GLEW::GLEW)
target_link_libraries(app PRIVATE my_library)
#target_link_libraries(app PRIVATE stb)
# For STB (header-only)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/../dependencies/stb/include)

#target_link_libraries(app PRIVATE glm)
# For GLM (header-only)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/../dependencies/glm)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/../dependencies/assimp/include)
target_link_libraries(app PRIVATE ${CMAKE_SOURCE_DIR}/../dependencies/assimp/build/bin/libassimp.so)
