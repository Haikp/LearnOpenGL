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
        //vertices            //normals            //texcoords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
    mesh.SetAttribStride(8);
    mesh.LinkAttrib(3);
    mesh.LinkAttrib(3);
    mesh.LinkAttrib(2);

    //compile shaders
    //for the cube that will be lit up
    Shader shaderProgram(path_to_vertex_shader.c_str(), path_to_fragment_shader.c_str());
    //for the cube that is the light source
    Shader lightingProgram(path_to_lighting_vertex_shader.c_str(), path_to_lighting_fragment_shader.c_str());
    shaderProgram.use();

    unsigned int texture, specmap;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int width, height, nrChannels;
    unsigned char* data = stbi_load((path_to_textures + "steelcrate.png").c_str(), &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load steelcrate.png" << std::endl;
    }

    stbi_image_free(data);

    glGenTextures(1, &specmap);
    glBindTexture(GL_TEXTURE_2D, specmap);

    data = stbi_load((path_to_textures + "steelcratespecmap.png").c_str(), &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load steelcratespecmap.png" << std::endl;
    }

    stbi_image_free(data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specmap);

    shaderProgram.setInt("material.diffuse", 0);
    shaderProgram.setInt("material.specular", 1);
    shaderProgram.setFloat("material.shininess", 32.0f); //how well the object will reflect the light, sharpness in appearance of the light

    glEnable(GL_DEPTH_TEST);

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraOrientiation = glm::vec3(0.0f, 1.0f, 0.0f);

    Camera camera(cameraPosition, cameraFront, cameraOrientiation, xWindowSize, yWindowSize);

    glm::mat4 projection = glm::perspective(glm::radians(fov), ((float)xWindowSize / (float)yWindowSize), 0.1f, 100.0f);

    glm::vec3 cubePositions[] =
    {
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

    glm::vec3 lightPos = glm::vec3(glm::vec3(0.0f, 0.0f, -10.0f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        camera.TakeInputs(window);

        glfwSetScrollCallback(window, scroll_callback);

        glClearColor(.0f, .0f, .0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //begin rendering main cube
        shaderProgram.use();

        shaderProgram.setVec3("cameraPosition", camera.getPosition());

        shaderProgram.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

        shaderProgram.setVec3("dirLight.ambient", glm::vec3(0.05f));
        shaderProgram.setVec3("dirLight.diffuse", glm::vec3(0.25f));
        shaderProgram.setVec3("dirLight.specular", glm::vec3(0.5f));

        shaderProgram.setVec3("pointLights[0].position", lightPos);

        //for a light source that diminishes with range
        shaderProgram.setFloat("pointLights[0].constant", 1.0f);
        shaderProgram.setFloat("pointLights[0].linear", 0.09f);
        shaderProgram.setFloat("pointLights[0].quadratic", 0.032f);

        //changes the actual color of the light
        shaderProgram.setVec3("pointLights[0].ambient", glm::vec3(0.05f));
        shaderProgram.setVec3("pointLights[0].diffuse", glm::vec3(0.6f));
        shaderProgram.setVec3("pointLights[0].specular", glm::vec3(0.7f));

        shaderProgram.setVec3("spotLight.position", camera.getPosition());

        //for a light source that diminishes with range
        shaderProgram.setFloat("spotLight.constant", 1.0f);
        shaderProgram.setFloat("spotLight.linear", 0.09f);
        shaderProgram.setFloat("spotLight.quadratic", 0.032f);

        shaderProgram.setVec3("spotLight.orientationForward", camera.getFront());
        shaderProgram.setFloat("spotLight.cutOff", std::cos(glm::radians(12.5f)));
        shaderProgram.setFloat("spotLight.outerCutOff", std::cos(glm::radians(15.0f)));

        //changes the actual color of the light
        shaderProgram.setVec3("spotLight.ambient", glm::vec3(0.2f));
        shaderProgram.setVec3("spotLight.diffuse", glm::vec3(0.5f));
        shaderProgram.setVec3("spotLight.specular", glm::vec3(1.0f));

        shaderProgram.setMat4("projection", projection);
        shaderProgram.setMat4("view", camera.getViewMat());

        for (int i = 0; i < 10 ; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float rotate = 20.0f * i;
            //model = glm::rotate(model, glm::radians(rotate), glm::vec3(1.0f, 0.3f, 0.5f));

            shaderProgram.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //begin rendering light cube
        lightingProgram.use();

        glm::vec3 lightSourceColor = glm::vec3(1.0f, 1.0f, 1.0f);
        lightingProgram.setVec3("lightSourceColor", lightSourceColor);
        lightingProgram.setMat4("projection", projection);
        lightingProgram.setMat4("view", camera.getViewMat());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
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
