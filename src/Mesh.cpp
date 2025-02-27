#include "mesh.h"

Mesh::VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void Mesh::VAO::Bind()
{
    glBindVertexArray(ID);
}

void Mesh::VAO::Unbind()
{
    glBindVertexArray(0);
}

void Mesh::VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}

Mesh::VBO::VBO()
{
    glGenBuffers(1, &ID);
}

void Mesh::VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Mesh::VBO::BufferData(std::vector<float> vertices)
{
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}

void Mesh::VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}

Mesh::EBO::EBO()
{
    glGenBuffers(1, &ID);
}

void Mesh::EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void Mesh::EBO::BufferData(std::vector<unsigned int> indices)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);
}

void Mesh::EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}

void Mesh::Bind()
{
    VAO.Bind();
    VBO.Bind();
    EBO.Bind();
}

void Mesh::Unbind()
{
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::SetAttribStride(unsigned int attribStride)
{
    this->attribStride = attribStride;
}

void Mesh::LinkAttrib(int indexSize)
{
    glVertexAttribPointer(attribCount, indexSize, GL_FLOAT, GL_FALSE, attribStride * sizeof(float), (void*)(attribOffset * sizeof(float)));
    glEnableVertexAttribArray(attribCount);

    attribCount++;
    attribOffset += indexSize;
}

void Mesh::VerifyValidAttrib()
{
    if (attribOffset < attribStride)
    {
        std::cerr << "VERTEX::ATTRIB::POINTER::SIZE::INVALID::OFFSET_LESS_THAN_STRIDE" << std::endl;
    }

    if (attribOffset > attribStride)
    {
        std::cerr << "VERTEX::ATTRIB::POINTER::SIZE::INVALID::OFFSET_LESS_THAN_STRIDE" << std::endl;
    }

    if (attribOffset == attribStride)
    {
        std::cout << "VERTEX::ATTRIB::POINTER::SIZE::VALID" << std::endl;
    }
}

void Mesh::Delete()
{
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
}
