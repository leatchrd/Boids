#pragma once
#include "p6/p6.h"

class VBO {
private:
    GLuint id;

public:
    VBO(GLuint id)
        : id{id} {};
    ~VBO() { glDeleteBuffers(1, &this->id); };

    inline void gen() { glGenBuffers(1, &this->id); };
    inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, this->id); };
    inline void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
};
