#include "submarine.hpp"
#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

// --- PUBLIC ---

Submarine::Submarine()
    : position{0.0f, 0.0f, 0.0f}, radius{0.2f}, vbo{3}, vao{3}
{
    this->vbo.gen();
    this->vbo.bind();
    glBufferData(GL_ARRAY_BUFFER, this->submarine.vertices.size() * sizeof(vertex), this->submarine.vertices.data(), GL_STATIC_DRAW);
    this->vbo.unbind();

    this->vao.gen();
    this->vao.bind();
    this->vao.activateAttributes();

    this->vbo.bind();
    this->vao.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    this->vbo.unbind();
    this->vao.unbind();
}

void Submarine::update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, float sideSize)
{
    this->updatePosition(ctx, sideSize);
    this->draw(ctx, camMVMatrix, uniMVP, uniMV, uniNormal);
}

// --- PRIVATE ---

void Submarine::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal)
{
    drawMesh(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, this->position, 0.f, glm::vec3{0.0f, 0.0f, 0.0f}, this->radius, this->submarine.vertices);
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
