#pragma once
#include "p6/p6.h"

class VAO {
private:
    GLuint _id;

public:
    VAO(GLuint id)
        : _id{id} {};
    ~VAO() { glDeleteVertexArrays(1, &this->_id); };

    inline void gen() { glGenVertexArrays(1, &this->_id); };
    inline void bind() { glBindVertexArray(this->_id); };
    inline void unbind() { glBindVertexArray(0); };
};