#include "fish.hpp"
#include "loader.h"

Fish::Fish()
    : vbo{1}, vao{1}
{
    vbo.gen();
    vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, this->fish.vertices.size() * sizeof(vertex), this->fish.vertices.data(), GL_STATIC_DRAW);
    vbo.unbind();

    vao.gen();
    vao.bind();
    vao.activateAttributes();

    vbo.bind();
    vao.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    vbo.unbind();
    vao.unbind();
}
