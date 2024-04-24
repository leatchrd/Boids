#include "coral.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "texture.hpp"
#include "vao.hpp"
#include "vbo.hpp"

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

void Coral::update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, Texture& texCoral1, Texture& texCoral2)
{
    texCoral1.bind();
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{1.25f, -2.0f, -1.2f}, 140.0f, 3.0f);
    texCoral1.unbind();

    texCoral2.bind();
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{1.5f, -2.0f, -0.2f}, 110.0f, 2.0f);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, glm::vec3{-1.4f, -2.0f, -1.4f}, -130.0f, 2.2f);
    texCoral2.unbind();
}

void Coral::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, glm::vec3 position, float angle, float scale)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, position);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // adjust object
    MVMatrix = glm::rotate(MVMatrix, glm::radians(angle), glm::vec3{0.0f, 1.0f, 0.0f});
    MVMatrix = glm::scale(MVMatrix, glm::vec3{scale});

    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // draw using the VAO
    glDrawArrays(GL_TRIANGLES, 0, this->coral.vertices.size());
}
