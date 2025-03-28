#include "bettermesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setUpMesh();
}

void Mesh::Draw(Shader &shader)
{
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
         else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    for (size_t i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::PrintData()
{
    std::cout << "VERTICES.POSITION" << std::endl;

    for (int i = 0; i < vertices.size(); i++)
    {
         std::cout << vertices[i].position[0] << " " << vertices[i].position[1] << " " << vertices[i].position[2] << std::endl;
    }

    std::cout << "VERTICES.NORMALS" << std::endl;

    for (int i = 0; i < vertices.size(); i++)
    {
         std::cout << vertices[i].normal[0] << " " << vertices[i].normal[1] << " " << vertices[i].normal[2] << std::endl;
    }

    std::cout << "\nVERTICES.TEXCOORDS" << std::endl;

    for (int i = 0; i < vertices.size(); i++)
    {
         std::cout << vertices[i].texCoords[0] << " " << vertices[i].texCoords[1] << std::endl;
    }

    std::cout << "\nINDICES" << std::endl;

    for (int i = 0; i < indices.size(); i++)
    {
         std::cout << indices[i] << std::endl;
    }
}

void Mesh::setUpMesh()
{
    //we already have the reference holders of unsigned ints intialized
    //next step to generate the buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //bind buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //insert data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(unsigned int), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    // Delete VAO, VBO, and EBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // Delete textures
    for (const Texture &texture : textures) {
        glDeleteTextures(1, &texture.id);
    }
}

