#include "cube.hpp"
// #include "loader.h"
#include "3DTools.hpp"
#include "vao.hpp"
#include "vbo.hpp"

Cube::Cube()
    : vbo{2}, vao{2}
{
    vbo.gen();
    vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, this->cube.size() * sizeof(Vertex2DTex), this->cube.data(), GL_STATIC_DRAW);
    vbo.unbind();

    vao.gen();
    vao.bind();
    vao.activateAttributes();

    vbo.bind();
    vao.setAttribPointer(sizeof(Vertex2DTex), (const GLvoid*)(offsetof(Vertex2DTex, position)), (const GLvoid*)(offsetof(Vertex2DTex, texture)));

    vbo.unbind();
    vao.unbind();
}
