#include "submarine.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
// #include "trackballCamera.hpp"
#include "vao.hpp"
#include "vbo.hpp"

// --- PUBLIC ---

Submarine::Submarine()
    : position{0.0f, 0.0f, 0.0f}, radius{0.2f}, vbo{3}, vao{3}
{
    vbo.gen();
    vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, this->submarine.vertices.size() * sizeof(vertex), this->submarine.vertices.data(), GL_STATIC_DRAW);
    vbo.unbind();

    vao.gen();
    vao.bind();
    vao.activateAttributes();

    vbo.bind();
    vao.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    vbo.unbind();
    vao.unbind();
}

void Submarine::update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, float wall)
{
    this->updatePosition(ctx, wall);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal);
}

// --- PRIVATE ---

void Submarine::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, this->position);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // adjust object
    // MVMatrix = glm::rotate(MVMatrix, glm::radians(90.f), glm::vec3{0.0f, 1.0f, 0.0f});
    MVMatrix = glm::scale(MVMatrix, glm::vec3{this->radius, this->radius, this->radius});

    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // draw using the VAO
    glDrawArrays(GL_TRIANGLES, 0, this->submarine.vertices.size());
}

void Submarine::moveFront(float delta, float wall)
{
    if (this->position.x <= -wall + (this->radius * 2.2) || this->position.x >= wall - (this->radius * 2.5))
    {
        this->position.x += (delta * 5);
    }
    else
    {
        this->position.x -= delta;
    }
}

void Submarine::moveLeft(float delta, float wall)
{
    if (this->position.z <= -wall + (this->radius * 1.1) || this->position.z >= wall - (this->radius * 1.1))
    {
        this->position.z -= (delta * 5);
    }
    else
    {
        this->position.z += delta;
    }
}

void Submarine::moveUp(float delta, float wall)
{
    if (this->position.y <= -wall + (this->radius * 1.1) || this->position.y >= wall - (this->radius * 2.5))
    {
        this->position.y -= (delta * 5);
    }
    else
    {
        this->position.y += delta;
    }
}

// void Submarine::rotateUp(float degrees)
// {
// }

// void Submarine::rotateLeft(float degrees)
// {
// }

void Submarine::updatePosition(p6::Context& ctx, float wall)
{
    if (ctx.key_is_pressed(GLFW_KEY_W)) // front
    {
        this->moveFront(ctx.delta_time(), wall);
    }
    if (ctx.key_is_pressed(GLFW_KEY_S)) // back
    {
        this->moveFront(-ctx.delta_time(), wall);
    }
    if (ctx.key_is_pressed(GLFW_KEY_A)) // left
    {
        this->moveLeft(ctx.delta_time(), wall);
    }
    if (ctx.key_is_pressed(GLFW_KEY_D)) // right
    {
        this->moveLeft(-ctx.delta_time(), wall);
    }
    if (ctx.key_is_pressed(GLFW_KEY_SPACE)) // up
    {
        this->moveUp(ctx.delta_time(), wall);
    }
    if (ctx.key_is_pressed(GLFW_KEY_LEFT_CONTROL)) // down
    {
        this->moveUp(-ctx.delta_time(), wall);
    }
}
