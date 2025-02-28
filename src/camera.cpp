#include "camera.h"

bool Camera::firstMouse = true;
float Camera::lastX = 0.0f;
float Camera::lastY = 0.0f;
float Camera::xoffset = 0.0f;
float Camera::yoffset = 0.0f;
float Camera::mouseSens = 0.1f;
float Camera::yaw = 0.0f;
float Camera::pitch = 0.0f;
glm::vec3 Camera::cameraPosition = glm::vec3(0.0f);
glm::vec3 Camera::cameraForward = glm::vec3(0.0f);
glm::vec3 Camera::cameraUp = glm::vec3(0.0f);

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraForward, glm::vec3 cameraUp, unsigned int xWindowSize, unsigned int yWindowSize)
{
    this->cameraPosition = cameraPosition;
    this->cameraForward = cameraForward;
    this->cameraUp = cameraUp;
    view = glm::lookAt(cameraPosition, cameraForward, cameraUp);

    lastX = xWindowSize/2;
    lastY = yWindowSize/2;
}

void Camera::TakeInputs(GLFWwindow* window)
{
    glfwSetCursorPosCallback(window, mouse_callback);
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        deltaTime *= 2;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += (cameraSpeed * deltaTime) * cameraForward;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraForward, cameraUp)) * (cameraSpeed * deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= (cameraSpeed * deltaTime) * cameraForward;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraForward, cameraUp)) * (cameraSpeed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPosition += (cameraSpeed * deltaTime) * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPosition -= (cameraSpeed * deltaTime) * cameraUp;

    view = glm::lookAt(cameraPosition, cameraPosition + cameraForward, cameraUp);
}

glm::mat4 Camera::getViewMat()
{
    return view;
}

void Camera::setMouseSens(float mouseSens)
{
    this->mouseSens = mouseSens;
}

void Camera::setCameraSpeed(float cameraSpeed)
{
    this->cameraSpeed = cameraSpeed;
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    //answers how much did your mouse move from the last frame
    xoffset = xpos - lastX;
    //order is swapped here because y value increase from top to bottom
        // and we want a positive value for the offset
    yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= mouseSens;
    yoffset *= mouseSens;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    direction.y = std::sin(glm::radians(pitch));
    direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    cameraForward = glm::normalize(direction);
}
