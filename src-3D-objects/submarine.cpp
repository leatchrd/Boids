#include "submarine.hpp"
#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

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
    drawMesh(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, this->position, 0.f, glm::vec3{0.0f, 0.0f, 0.0f}, this->radius, this->submarine.vertices);
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
