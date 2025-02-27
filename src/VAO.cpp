#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

VAO::Bind()
{
    glBindVertexArray(ID);
}

VAO::Unbind()
{
    glBindVertexArray(0);
}

VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}
