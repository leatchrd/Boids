#include "vao.hpp"
#include "p6/p6.h"

void VAO::activateAttributes()
{
    glEnableVertexAttribArray(this->_position);
    glEnableVertexAttribArray(this->_norm);
    glEnableVertexAttribArray(this->_texCoords);
}

void VAO::setAttribPointer(GLsizei stride, const GLvoid* pointerPosNorm, const GLvoid* pointerTex)
{
    glVertexAttribPointer(this->_position, 3, GL_FLOAT, GL_FALSE, stride, pointerPosNorm);
    glVertexAttribPointer(this->_norm, 3, GL_FLOAT, GL_FALSE, stride, pointerPosNorm);
    glVertexAttribPointer(this->_texCoords, 2, GL_FLOAT, GL_FALSE, stride, pointerTex);
}
