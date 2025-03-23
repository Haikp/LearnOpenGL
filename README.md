# My OpenGL Learning Journey (Repo on Hiatus, working on another repo)
This repo will contain mostly everything that I have learned about OpenGL, all separated in to branches. I will try to keep everything well documented, with a roadmap in this readme file, and perhaps more description as to what was learned other readme files in their respective branches.

## Requirements
Requirements will be different for each branch when looking at vendors/dependencies.

- CMake (v3.20+)
- OpenGL (v4.6+) (updated through kisak-mesa)
- Dependencies: GLFW, GLEW, glm, stb

## Building the Project
- Being in the correct directory ( the one with CMakeLists.txt in it ), run cmake
  - I use Dispatch with nvim, as such I run
`:Dispatch cmake`
- Run the generated makefile
`:Dispatch make`
- Run the generated file to view the created graphics
`:Dispatch ./src/app`
    - My CMake is set up such that the generated file is located in the src folder, along with the main code

## General OpenGL Workflow
#### This section is written after module 06_Cameras in order to gather my thoughts and develop a general workflow on what should be the next logical step when working with graphics. This will be on more of a general, technical overview.

Starting with initializing the OpenGL framework, we start stating the desired version and profile that we'll be using. Depending on the framework you are using, create a window and initialize the framework before continuing to begin the rendering process.

We are able to now create our shader program and compile our shaders, however before getting into the graphics pipeline, we must first create our data to output on to the screen. In doing so, we must interact with the various buffers and objects. The general steps towards working with these objects is to first allocate space that references these objects, generate the objects, bind the objects, then begin loading the data into these objects. Starting from top to bottom on what these objects take, the VAO can be seen as a hashmap that holds the reference to the VBO and EBO. The VAO must be created and binded first before the others so that it is aware that we are loading the following buffers to this particular VAO. Next is the VBO, which the data we insert into here is the individual vertex data involving the coordinates, color, and texture coordinates. The EBO refers to the order specified to draw the shape. This allows for us to reuse certain vertices when drawing, thus saving more space. With the nature of low level programming, we must now specify how OpenGL should process our information passed into the VBO. Essentially, OpenGL reads through the VBO with a pointer, and we have to specify how many bytes open has to move the pointer to read a specific type of information, and thus completing our buffers and objects. The next data to insert would be the images, which behave in a similar manner to how we work with objects and buffers. Again, allocate space that holds the refernce to the images, generate the space, then being inserting data. However, before we insert data, we should specify the settings we want for our image, describing its nature when the image is far away, or if the texture coordinates does not reach the edge of the objects. Once the image has been loaded, it is good practice to free the data used to load the image, as we have the reference to our inserted data else where already.

Now that our data has been inserted and parsed, we can now begin working with the pipeline. Starting with the Vertex Shader, the only purpose that I have seen about this shader is to generate the primitive in local space, then promptly move the shape in world space. The data in which it uses for the vertices is read in through the VBO and EBO, being read through their respective locations and drawn appropriately. As for the fragment shader, this shader begins to fill in the primitives and provide it with our specified color and texture. To note, texture is set via uniforms on the CPU, or main.cpp, meaning it is sent as a global. This information about the two shaders is very shallow, as the modules I am following have yet to completely go indepth with these shaders, however I am aware that they will be more interactive with them later down the line. Something to note about uniforms, you must set uniforms after stating which shader program you are using.

Lastly, it is now time for controlling the camera properly. For a general understanding of how to approach cameras, there are 3 important components, the model matrix, the view matrix, and the projection matrix. Have in mind where the objects in your space should be in comparison to the camera, this is what the model matrix represents. As for the view matrix, determine the angle in which you want the camera to look at after determining the camera's position. As for the project matrix, this represents the frustum of the camera, determine how you want to capture the scene, be it like a normal camera in a pyramid shape, or in a cube frustum.

This didn't get into anything too detailed, because that's what the individual README.md files are for in each module, going more indepth about how to approach each section. I just wanted to write this section just as a review since the modules I'm following marks this point (end of module 6) to be the end of the basics. Moving on to the next topic from here, lighting.

#### This section is written after module 11_MultipleLights
Initially I had wanted this to be something I can refer back to when I was when I needed to look back for something, or as some small guide or something, but this in itself is not very organized. This whole repo more or less serves to show that I put in some work in the days that I contributed to this repo. An independent project needs to and will come out of this project to show that I have some competence and understanding of OpenGL. I have an idea about what I want to make already, and hopefully it'll turn out good, but I'll need to get through the loading models modules first before I can making something of that.

Anyways, about the sections that I have covered since Cameras, a majority of the learning has been more about mathematical concepts and how it can be applied to create something. There isn't any new work flow that should be considered as a whole, lighting should vary depending on the setting. If you want to know more about the mathematical side of it, take a look at the README.md files associated to the topic you want. I believe I did the best I could in explaining how the math works on a conceptual level, but there is a lot to read.
