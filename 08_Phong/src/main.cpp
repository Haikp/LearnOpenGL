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
std::string path_to_lighting_vertex_shader = std::string(TOSTRING(SHADER_PATH)) + "lighting_vertex_shader.glsl";
std::string path_to_lighting_fragment_shader = std::string(TOSTRING(SHADER_PATH)) + "lighting_fragment_shader.glsl";
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
        //vertices
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
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
    mesh.SetAttribStride(3);
    mesh.LinkAttrib(3);

    //compile shaders
    //for the cube that will be lit up
    Shader shaderProgram(path_to_vertex_shader.c_str(), path_to_fragment_shader.c_str());
    //for the cube that is the light source
    Shader lightingProgram(path_to_lighting_vertex_shader.c_str(), path_to_lighting_fragment_shader.c_str());
    shaderProgram.use();

    //set the color of the objecti
    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);

    //set light color that will change the color of the object
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraOrientiation = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera camera(cameraPosition, cameraFront, cameraOrientiation, xWindowSize, yWindowSize);

    glm::mat4 projection = glm::perspective(glm::radians(fov), ((float)xWindowSize / (float)yWindowSize), 0.1f, 100.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        camera.TakeInputs(window);

        glfwSetScrollCallback(window, scroll_callback);

        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //begin rendering main cube
        glm::mat4 model = glm::mat4(1.0f);

        shaderProgram.use();
        shaderProgram.setVec3("objectColor", objectColor);
        shaderProgram.setVec3("lightColor", lightColor);
        shaderProgram.setMat4("projection", projection);
        shaderProgram.setMat4("view", camera.getViewMat());
        shaderProgram.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        //begin rendering light cube
        lightingProgram.use();
        lightingProgram.setMat4("projection", projection);
        lightingProgram.setMat4("view", camera.getViewMat());

        model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
        lightingProgram.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
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
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
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
