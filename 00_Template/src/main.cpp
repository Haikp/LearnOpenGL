#include <iostream>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

void processInput(GLFWwindow*);

const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}\0";

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
        .0f, .5f, .0f,
        -.5f, -.5f, .0f,
        .5f, -.5f, .0f
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // tells OpenGL how to read the buffer we sent properly
    glEnableVertexAttribArray(0);

    //compile shaders
    unsigned int vertexShader; //location of vertexShader data
    vertexShader = glCreateShader(GL_VERTEX_SHADER); //establishes variable as a vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //implant the vertex shader code
    glCompileShader(vertexShader);

    int success = 0;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram(); //creates shader program/pipeline that geometry will go through
    glAttachShader(shaderProgram, vertexShader); //insert vertex shader
    glAttachShader(shaderProgram, fragmentShader); //insert fragment shader
    glLinkProgram(shaderProgram); //links all shaders in the correct order to be executed

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glClearColor(.0f, .0f, .0f, 1.0f);

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
