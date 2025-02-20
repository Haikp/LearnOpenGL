cmake_minimum_required(VERSION 3.20)
project(test_project VERSION 0.1.0)

#for code reusability and cleanliness
add_definitions(-DSHADER_PATH=${CMAKE_SOURCE_DIR}/shaders/)
add_definitions(-DTEXTURE_PATH=${CMAKE_SOURCE_DIR}/textures/)

add_executable(app src/main.cpp)

set(OSBitness 32)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBitness 64)
endif()

#organizational preference
set (FullOutputDir "${CMAKE_SOURCE_DIR}/build/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

set_target_properties(app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir}
)

#uses include_directories because it does not have its own CMakeLists.txt to help with configuration
include_directories(${CMAKE_SOURCE_DIR}/../include)
#adding a second parameter of where the dependencies should be built to allows for out of tree directories to be used
#uses add_subdirectory and not include_directories is because stb has its own CMakeLists.txt for its own config
add_subdirectory(${CMAKE_SOURCE_DIR}/../dependencies/stb ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

#would need to add stb if there was an implementation file, however stb's own CMakeLists already adds it
add_library(my_library SHARED
    ../src/shaders.cpp
)

#i know that the cmake prefix path helps with locating glfw3 and glew,
#but im not sure as to how opengl is found, but its clear that capitalization matters
set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glfw3/glfw3Config.cmake" ${CMAKE_PREFIX_PATH})
set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glew/glew-config.cmake" ${CMAKE_PREFIX_PATH})
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

#how these libraries are named, apparently most of these are either provided by the system your using, or are created by the .cmake files and are standard
target_link_libraries(app PRIVATE glfw3)
target_link_libraries(app PRIVATE glfw3 dl)
target_link_libraries(app PRIVATE glfw3 ${OPENGL_LIBRARIES} pthread)
target_link_libraries(app PRIVATE GLEW::GLEW)
#variaable name my_library defined above
target_link_libraries(app PRIVATE my_library)
#parameter stb is the from the library named stb in the CMakeLists.txt in stb
target_link_libraries(app PRIVATE stb)
