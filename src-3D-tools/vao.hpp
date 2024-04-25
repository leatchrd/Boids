#pragma once
#include "p6/p6.h"

class VAO {
private:
    GLuint                  id;
    static constexpr GLuint position  = 0;
    static constexpr GLuint norm      = 1;
    static constexpr GLuint texCoords = 2;

public:
    VAO(GLuint id)
        : id{id} {};
    ~VAO() { glDeleteVertexArrays(1, &this->id); };

    inline void gen() { glGenVertexArrays(1, &this->id); };
    inline void bind() { glBindVertexArray(this->id); };
    inline void unbind() { glBindVertexArray(0); };

    void activateAttributes();
    void setAttribPointer(GLsizei stride, const GLvoid* pointerPosNorm, const GLvoid* pointerTex);
};
