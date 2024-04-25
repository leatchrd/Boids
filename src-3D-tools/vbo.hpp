#pragma once
#include "p6/p6.h"

class VBO {
private:
    GLuint _id;

public:
    VBO(GLuint id)
        : _id{id} {};
    ~VBO() { glDeleteBuffers(1, &this->_id); };

    inline void gen() { glGenBuffers(1, &this->_id); };
    inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, this->_id); };
    inline void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
};
