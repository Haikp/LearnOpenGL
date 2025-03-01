#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include "shaders.h"
#include "mesh.h"
#include "camera.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processInput(GLFWwindow*);
void scroll_callback(GLFWwindow*, double, double);
glm::mat4 myLookAt(glm::vec3, glm::vec3, glm::vec3);

//just for dynamic purposes for future projects
std::string path_to_vertex_shader = std::string(TOSTRING(SHADER_PATH)) + "vertex_shader.glsl";
std::string path_to_fragment_shader = std::string(TOSTRING(SHADER_PATH)) + "fragment_shader.glsl";
std::string path_to_textures = std::string(TOSTRING(TEXTURE_PATH));

const int xWindowSize = 1080;
const int yWindowSize = 720;

float fov = 45.0f;

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
    std::vector<float> vertices = {
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

    std::vector<unsigned int> indices;

    for (int i = 0; i < 36; i++)
    {
        indices.push_back(i);
    }

    Mesh mesh; //creates and generates 1 buffer for VAO, VBO, and EBO
    mesh.Bind(); //binds all 3
    //insert data accordingly
    mesh.VBO.BufferData(vertices);
    mesh.EBO.BufferData(indices);

    //on to attrib pointer
    mesh.SetAttribStride(5);
    mesh.LinkAttrib(3);
    mesh.LinkAttrib(2);

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

    glEnable(GL_DEPTH_TEST);
    float transparency = 0.3f;

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraOrientiation = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera camera(cameraPosition, cameraFront, cameraOrientiation, xWindowSize, yWindowSize);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glm::mat4 projection = glm::perspective(glm::radians(fov), ((float)xWindowSize / (float)yWindowSize), 0.1f, 100.0f);
        shaderProgram.setMat4("projection", projection);

        camera.TakeInputs(window);

        shaderProgram.setMat4("view", camera.getViewMat());

        glfwSetScrollCallback(window, scroll_callback);

        shaderProgram.setFloat("transparency", transparency);
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            transparency += .01;

        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            transparency -= .01;

        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float timeSinceStart = glfwGetTime();

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

    mesh.Unbind();
    mesh.Delete();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

//keep in mind that in there should be no matrix computations to be done here, rather we are just trying to create a view matrix based on inputted values
//at this point in the code, the rotation as been done already, its just a matter of placing it in the correct orientation.
glm::mat4 myLookAt(glm::vec3 cameraPosition, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
    // Compute the forward vector
    glm::vec3 forward = glm::normalize(cameraPosition - cameraFront);

    // Compute the right vector
    glm::vec3 right = glm::normalize(glm::cross(glm::normalize(cameraUp), forward));

    // Compute the actual up vector
    glm::vec3 up = glm::cross(forward, right);

    // Construct the view matrix manually
    // TO NOTE, THIS IS COLUMN MAJOR, MEANING FOLLOWING WHAT YOU LEARNED IN MATH, first index is row, second index is column, matrix vector mult is matrix * vector still
    // view [row][column]
    // read "going down the column"
    glm::mat4 view = glm::mat4(1.0f);
    view[0][0] = right.x;
    view[1][0] = right.y;
    view[2][0] = right.z;
    view[3][0] = -glm::dot(right, cameraPosition);

    view[0][1] = up.x;
    view[1][1] = up.y;
    view[2][1] = up.z;
    view[3][1] = -glm::dot(up, cameraPosition);

    view[0][2] = forward.x;
    view[1][2] = forward.y;
    view[2][2] = forward.z;
    view[3][2] = -glm::dot(forward, cameraPosition);

    return view;
}
