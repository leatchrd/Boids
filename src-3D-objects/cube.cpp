#include "cube.hpp"
#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

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

void Cube::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, float sideSize)
{
    drawMesh(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, glm::vec3{0.0f, 0.0f, 0.0f}, 0.0f, glm::vec3{0.0f, 1.0f, 0.0f}, sideSize, this->cube);
}
