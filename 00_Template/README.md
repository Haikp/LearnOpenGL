# My OpenGL Learning Journey
This repo will contain mostly everything that I have learned about OpenGL, all separated in to branches. I will try to keep everything well documented, with a roadmap in this readme file, and perhaps more description as to what was learned other readme files in their respective branches.

## Requirements
Requirements will be different for each branch when looking at vendors/dependencies.

- CMake (v3.20+)
- OpenGL (v4.6+) (updated through kisak-mesa)
- Dependencies: GLFW, GLEW

## Building the Project
- Being in the correct directory ( the one with CMakeLists.txt in it ), run cmake
  - I use Dispatch with nvim, as such I run
`:Dispatch cmake`
- Run the generated makefile
`:Dispatch make`
- Run the generated file to view the created graphics
`:Dispatch ./src/app`
    - My CMake is set up such that the generated file is located in the src folder, along with the main code

## Contents of This Branch
This branch contains the barebones of an OpenGL project, which this can be seen as template that updates according to what I've learned. Whether or not this repo gets convoluted with dependencies will be up to how overbearing it looks in the future.

## Roadmap
The order of progression:
- main
- [triangle](https://github.com/Haikp/OpenGLRevisited/tree/triangle)
