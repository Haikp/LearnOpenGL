#include "Mesh.h"

Mesh::VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

Mesh::VAO:Bind()
{
    glBindVertexArray(ID);
}

Mesh::VAO::Unbind()
{
    glBindVertexArray(0);
}

Mesh::VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}

Mesh::VBO::VBO()
{
    glGenBuffers(1, &ID);
}

Mesh::VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

Mesh::VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}

Mesh::EBO::EBO()
{
    glGenBuffers(1, &ID);
}

Mesh::EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

Mesh::EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}

Mesh::Bind()
{
    VAO.Bind();
    VBO.Bind();
    EBO.Bind();
}

Mesh::Unbind()
{
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

Mesh::LinkAttrib()
{

}

Mesh::Delete()
{
    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
}
