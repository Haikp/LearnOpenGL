#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <iostream>
#include <vector>

class Mesh
{
public:
    class VAO
    {
        friend class Mesh;
    public:
    private:
        unsigned int ID;
        VAO();
        void Bind();
        void Unbind();
        void Delete();
    };

    class VBO
    {
        friend class Mesh;
    public:
        void BufferData(std::vector<float>);
    private:
        unsigned int ID;
        VBO();
        void Bind();
        void Unbind();
        void Delete();
    };

    class EBO
    {
        friend class Mesh;
    public:
        void BufferData(std::vector<unsigned int>);
    private:
        unsigned int ID;
        EBO();
        void Bind();
        void Unbind();
        void Delete();
    };

    VAO VAO;
    VBO VBO;
    EBO EBO;

    void Bind();
    void Unbind();
    void SetAttribStride(unsigned int attribStride);
    void LinkAttrib(int indexSize);
    void VerifyValidAttrib();
    void Delete();

    ~Mesh() {
        Unbind();
        Delete();  // Calls Delete() to clean up the resources when Mesh is destroyed
    }

private:
    unsigned int attribCount = 0;
    unsigned int attribStride = 0;
    unsigned int attribOffset = 0;
    bool isValidStride;
};

#endif
