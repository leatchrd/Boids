#include "fish.hpp"
#include "loader.h"

Fish::Fish()
    : vbo{1}, vao{1}
{
    this->vbo.gen();
    this->vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, this->fish.vertices.size() * sizeof(vertex), this->fish.vertices.data(), GL_STATIC_DRAW);
    this->vbo.unbind();

    this->vao.gen();
    this->vao.bind();
    this->vao.activateAttributes();

    this->vbo.bind();
    this->vao.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    this->vbo.unbind();
    this->vao.unbind();
}
