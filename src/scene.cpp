#include "scene.hpp"
#include "flock.hpp"
#include "p6/p6.h"
#include "tools.hpp"

Scene::Scene(glm::vec2 position, float side)
{
    this->position = position;
    this->side     = side;
}

void Scene::draw(p6::Context& ctx, float radius)
{
    // background
    ctx.background(p6::NamedColor::Blue);
    // cube
    drawSquare(ctx, this->position, this->side);
    // circle that follows mouse
    drawCircle(ctx, ctx.mouse(), radius);
}

bool Scene::collisionWithWall(Boid& boid)
{
    return boid.onWall(this->side);
}

// Event management

void Scene::dealWithWallCollisions(Flock& flock)
{
    for (size_t i = 0; i < flock.flock.size(); i++)
    {
        if (this->collisionWithWall(flock.flock[i]))
        {
            flock.flock[i].newDirectionWall();
        }
    }
}

void Scene::dealWithFKeyPressed(p6::Context& ctx, Flock& flock, glm::vec2 force)
{
    if (ctx.key_is_pressed(GLFW_KEY_F))
    {
        flock.addForce(force);
    }
}
