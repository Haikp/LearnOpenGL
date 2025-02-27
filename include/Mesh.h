#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
    VAO VAO();
    VBO VBO();
    EBO EBO();

    class VAO
    {
    public:
    private:
        unsigned int ID;
        VAO();
        Bind();
        Unbind();
        Delete();
    };

    class VBO
    {
    public:
        BufferData();
    private:
        unsigned int ID;
        VBO();
        Bind();
        Unbind();
        Delete();
    };

    class EBO
    {
    public:
        BufferData();
    private:
        unsigned int ID;
        EBO();
        Bind();
        Unbind();
        Delete();
    };

    Bind();
    Unbind();
    LinkAttrib();
    Delete();
private:
};

#endif
