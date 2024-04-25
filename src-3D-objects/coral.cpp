#include "coral.hpp"
#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "texture.hpp"

Coral::Coral()
    : vbo{4}, vao{4}
{
    vbo.gen();
    vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, this->coral.vertices.size() * sizeof(vertex), this->coral.vertices.data(), GL_STATIC_DRAW);
    vbo.unbind();

    vao.gen();
    vao.bind();
    vao.activateAttributes();

    vbo.bind();
    vao.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    vbo.unbind();
    vao.unbind();
}

void Coral::update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, Texture& texCoral1, Texture& texCoral2, Texture& texCoral3)
{
    texCoral1.bind();
    this->draw(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, glm::vec3{-1.4f, -2.0f, -1.4f}, -130.0f, 2.2f);
    texCoral1.unbind();

    texCoral2.bind();
    this->draw(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, glm::vec3{1.5f, -2.0f, -0.2f}, 110.0f, 2.0f);
    texCoral2.unbind();

    texCoral3.bind();
    this->draw(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, glm::vec3{1.25f, -2.0f, -1.2f}, 140.0f, 3.0f);
    texCoral3.unbind();
}

void Coral::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, glm::vec3 position, float angle, float scale)
{
    drawMesh(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, position, glm::radians(angle), glm::vec3{0.0f, 1.0f, 0.0f}, scale, this->coral.vertices);
}
