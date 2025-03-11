#ifndef BETTER_MESH_H
#define BETTER_MESH_H

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>

#include "shaders.h"

#include <../dependencies/glm/glm/glm.hpp>
#include <../dependencies/glm/glm/gtc/matrix_transform.hpp>
#include <../dependencies/glm/glm/gtc/type_ptr.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
    void PrintData();
    ~Mesh();
private:
    unsigned int VAO, VBO, EBO;

    void setUpMesh();
};

#endif
