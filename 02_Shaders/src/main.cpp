#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "shaders.h"

void processInput(GLFWwindow*);

const char* path_to_vertex_shader = "02_Shaders/shaders/vertex_shader.glsl";
const char* path_to_fragment_shader = "02_Shaders/shaders/fragment_shader.glsl";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to init glew" << std::endl;
        glfwTerminate();
        return -1;
    }

    // establish vertices of geometry
    float vertices1[] = {
        //coordinates        //color
         0.0f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f
    };

    unsigned int indices1[] = {
        0, 1, 2
    };

    unsigned int VAO1; //create the object that will store references to attributes for shader usage
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    // create a vertex buffer array
    unsigned int VBO1; // location where we will store info about the vertex buffer
    glGenBuffers(1, &VBO1); // specify that we want to allocate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO1); // notify OpenGL that the array buffer is in use
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW); // place the array of values into the buffer

    unsigned int EBO1;
    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // tells OpenGL how to read the buffer we sent properly
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // tells OpenGL how to read the buffer we sent properly
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //compile shaders

    Shader shaderProgram(path_to_vertex_shader, path_to_fragment_shader);
    shaderProgram.use();

    shaderProgram.setFloat("offset", .5f);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glClearColor(.0f, .8f, .5f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
