#pragma once
#include "p6/p6.h"

class VAO {
private:
    GLuint                  _id;
    static constexpr GLuint _position  = 0;
    static constexpr GLuint _norm      = 1;
    static constexpr GLuint _texCoords = 2;

public:
    VAO(GLuint id)
        : _id{id} {};
    ~VAO() { glDeleteVertexArrays(1, &this->_id); };

    inline void gen() { glGenVertexArrays(1, &this->_id); };
    inline void bind() { glBindVertexArray(this->_id); };
    inline void unbind() { glBindVertexArray(0); };

    void activateAttributes();
    void setAttribPointer(GLsizei stride, const GLvoid* pointerPosNorm, const GLvoid* pointerTex);
};
