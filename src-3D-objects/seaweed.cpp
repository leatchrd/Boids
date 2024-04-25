#include "seaweed.hpp"
#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "texture.hpp"

Seaweed::Seaweed()
    : vbo{5}, vao{5}
{
    vbo.gen();
    vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, this->seaweed.vertices.size() * sizeof(vertex), this->seaweed.vertices.data(), GL_STATIC_DRAW);
    vbo.unbind();

    vao.gen();
    vao.bind();
    vao.activateAttributes();

    vbo.bind();
    vao.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    vbo.unbind();
    vao.unbind();
}

void Seaweed::update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, Texture& texSeaweed1, Texture& texSeaweed2)
{
    texSeaweed1.bind();
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-1.4f, -2.0f, 1.35f}, 0.0f, 0.6f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-0.45f, -2.0f, -1.5f}, 100.0f, 0.6f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-0.3f, -2.0f, 1.4f}, 140.0f, 0.6f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-0.9f, -2.0f, 0.2f}, 270.0f, 0.7f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{0.5f, -2.0f, 0.0f}, 70.0f, 0.7f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{0.25f, -2.0f, -1.6f}, 100.0f, 0.5f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{1.3f, -2.0f, 1.3f}, 100.0f, 0.6f);
    texSeaweed1.unbind();

    texSeaweed2.bind();
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-1.0f, -2.0f, 1.1f}, -80.0f, 0.5f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-0.4f, -2.0f, -0.2f}, -80.0f, 0.6f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-0.1f, -2.0f, -0.8f}, 10.0f, 1.0f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-1.1f, -2.0f, -0.5f}, 210.0f, 0.4f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-1.6f, -2.0f, 0.2f}, -50.0f, 0.3f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{0.3f, -2.0f, 0.9f}, 100.0f, 0.7f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{1.2f, -2.0f, 0.4f}, 100.0f, 0.5f);
    texSeaweed2.unbind();
}

void Seaweed::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, glm::vec3 position, float angle, float scale)
{
    drawMesh(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, position, angle, glm::vec3{0.0f, 1.0f, 0.0f}, scale, this->seaweed.vertices);
}
