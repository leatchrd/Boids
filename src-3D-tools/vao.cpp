#include "vao.hpp"
#include "p6/p6.h"

void VAO::activateAttributes()
{
    glEnableVertexAttribArray(this->position);
    glEnableVertexAttribArray(this->norm);
    glEnableVertexAttribArray(this->texCoords);
}

void VAO::setAttribPointer(GLsizei stride, const GLvoid* pointerPosNorm, const GLvoid* pointerTex)
{
    glVertexAttribPointer(this->position, 3, GL_FLOAT, GL_FALSE, stride, pointerPosNorm);
    glVertexAttribPointer(this->norm, 3, GL_FLOAT, GL_FALSE, stride, pointerPosNorm);
    glVertexAttribPointer(this->texCoords, 2, GL_FLOAT, GL_FALSE, stride, pointerTex);
}
