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
