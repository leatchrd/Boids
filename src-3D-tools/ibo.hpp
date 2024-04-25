#pragma once
#include "p6/p6.h"

class IBO {
private:
    GLuint _id;

public:
    std::vector<uint32_t> indices;

public:
    IBO(GLuint id)
        : _id{id} {};
    ~IBO() { glDeleteBuffers(1, &this->_id); };

    inline void gen() { glGenBuffers(1, &this->_id); };
    inline void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id); };
    inline void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
    inline void fill() { glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(uint32_t), this->indices.data(), GL_STATIC_DRAW); };
};
