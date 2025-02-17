# My OpenGL Learning Journey
This repo will contain mostly everything that I have learned about OpenGL, all separated in to branches. I will try to keep everything well documented, with a roadmap in this readme file, and perhaps more description as to what was learned other readme files in their respective branches.

### NOTE: The following notes I take on these branches correlate to the context of these branches, and not necessarily covering the whole scope of a topic.

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
In a thorough investigation to ensure I understand the general workflow of using opengl at a beginner level, I looked into understanding each of the functions to develop a general workflow to follow.

Creating a Desired Geometry:
To develop a geometry, first and foremost we must have the coordinates we wish to use, but more importantly must understand the purpose of array objects and buffers. There are three "OpenGL managed objects" that we should understand, the Vertex Array Object (VAO), Vertex Buffer Object (VBO), and the Element Buffer Array (EBO). The VAO to my understanding can be seen as a hashmap, where OpenGL is able to request information, and get a reference as an output. These potential references are the VBO and the EBO for the shaders down the line to use. The VBO serves as a vector, to which this will hold already organized data about the vertices to be drawn. Lastly, the EBO is a set of instructions that the shader is given, grouping the vertices that go together, and establishing an order that each geometry must be drawn.

Some things to note about when thinking about efficiency, there can be multiple VBOs and EBOs, all under the same VAO. To consider whether or not you need another VAO, if you needed to change glVertexAttribPointer, its probably best to use another VAO. If the information between the different VBO and EBOs are the same type (# of indices, is color coords, or texture coords), then keep in the same VAO. Within this branch shows an example of how multiple VBOs and EBOs are used under one VAO.

A workflow to help understand the process more:
- allocate space (VAO, VBO, EBO)
- generate desired amount (VAO, VBO, EBO)
- bind accordingly(VAO, VBO, EBO)
- insert data (VBO, EBO)
- tell opengl how to read the VBO data glVertexAttribPointer()
- enable the vertexattribpointer

Using Shaders:
For now in this branch, we will not cover how to write your own shaders just yet, as such heres the general workflow for using them:
- allocate space per shader
- insert information
- compile the shaders
  - check if the shaders compiled successfully
- create a shader program to follow
- attach the desired shaders
- link the shaders together
- delete the no longer needed shaders
- run the program before rendering

## Roadmap
The order of progression:
- [main](https://github.com/Haikp/OpenGLRevisited/tree/main)
- triangle
