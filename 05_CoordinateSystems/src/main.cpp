#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cmath>
#include "shaders.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow*);

//just for dynamic purposes for future projects
std::string path_to_vertex_shader = std::string(TOSTRING(SHADER_PATH)) + "vertex_shader.glsl";
std::string path_to_fragment_shader = std::string(TOSTRING(SHADER_PATH)) + "fragment_shader.glsl";
std::string path_to_textures = std::string(TOSTRING(TEXTURE_PATH));

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int xWindowSize = 1080;
    const int yWindowSize = 720;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(xWindowSize, yWindowSize, "LearnOpenGL", NULL, NULL);
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
    float vertices[] = {
        //vertices            //texture coordinates
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[36]; //= { 0, 1, 2, 3, 4, 5};

    for (int i = 0; i < 36; i++)
    {
        indices[i] = i;
    }

    unsigned int VAO1; //create the object that will store references to attributes for shader usage
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    // create a vertex buffer array
    unsigned int VBO1; // location where we will store info about the vertex buffer
    glGenBuffers(1, &VBO1); // specify that we want to allocate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO1); // notify OpenGL that the array buffer is in use
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // place the array of values into the buffer

    unsigned int EBO1;
    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // tells OpenGL how to read the buffer we sent properly
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // tells OpenGL how to read the buffer we sent properly
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //compile shaders
    Shader shaderProgram(path_to_vertex_shader.c_str(), path_to_fragment_shader.c_str());
    shaderProgram.use();

    //load textures
    unsigned int tex0, tex1;
    glGenTextures(1, &tex0);
    glBindTexture(GL_TEXTURE_2D, tex0);

    int width, height, nrChannels;
    unsigned char *data = stbi_load((path_to_textures + "container.jpg").c_str(), &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load image0." << std::endl;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    glGenTextures(1, &tex1);
    glBindTexture(GL_TEXTURE_2D, tex1);

    data = stbi_load((path_to_textures + "awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load image1." << std::endl;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex1);

    shaderProgram.setInt("tex0", 0);
    shaderProgram.setInt("tex1", 1);

    //glm::mat4 model = glm::mat4(1.0f); //identity matrix, generic matrix that will represent out transformation
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //shaderProgram.setMat4("model", model);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    shaderProgram.setMat4("view", view);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), ((float)xWindowSize / (float)yWindowSize), 3.0f, 100.0f);
    projection = glm::rotate(projection, glm::radians(10.0f), glm::vec3(0.0f, 0.3f, 1.0f));
    shaderProgram.setMat4("projection", projection);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float transparency = 0.3f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        shaderProgram.setFloat("transparency", transparency);
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            transparency += .01;

        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            transparency -= .01;

        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float timeSinceStart = glfwGetTime();
        float sin = std::asin(std::sin(timeSinceStart));
        float cos = std::cos(timeSinceStart);

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            if(((i + 1) % 3) == 0)
                model = glm::rotate(model, glm::radians(timeSinceStart * 100), glm::vec3(0.0f, 1.0f, 0.0f));

            else if (i % 3 == 1)
                model = glm::rotate(model, glm::radians(timeSinceStart * 1000), glm::vec3(1.0f, 1.0f, 0.0f));

            else
                model = glm::rotate(model, glm::radians(timeSinceStart * 500), glm::vec3(1.0f, 0.0f, 0.0f));

            model = glm::rotate(model, glm::radians(timeSinceStart * 250), glm::vec3(0.0f, 1.0f, 1.0f));

            shaderProgram.setMat4("model", model);



            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &EBO1);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}
