#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>

class VAO
{
public:
    VAO();
    Bind();
    Delete();
    LinkAttrib();
private:
    unsigned int ID;

};

#endif
