#include "scene.hpp"
#include "GLFW/glfw3.h"
#include "flock.hpp"
#include "menu.hpp"
#include "p6/p6.h"
#include "tools.hpp"

Scene::Scene(glm::vec2 position)
    : position{position}, flock(5)
{
}

void Scene::draw(p6::Context& ctx, float radius)
{
    // background
    // ctx.background(p6::rgb(colorsBackground::Red, colorsBackground::Green, colorsBackground::Blue));
    ctx.background(backgroundColor);

    // cube
    drawSquare(ctx, this->position, this->side);
    // circle that follows mouse
    drawCircle(ctx, ctx.mouse(), radius);
}

void Scene::update(p6::Context& ctx)
{
    this->flock.update(ctx);
}

bool Scene::collisionWithWall(Boid& boid)
{
    return boid.onWall(this->side);
}

// Event management

void Scene::dealWithWallCollisions()
{
    for (size_t i = 0; i < flock.flock.size(); i++)
    {
        if (this->collisionWithWall(this->flock.flock[i]))
        {
            this->flock.flock[i].newDirectionWall();
        }
    }
}

void Scene::dealWithFKeyPressed(p6::Context& ctx, glm::vec2 force)
{
    if (ctx.key_is_pressed(GLFW_KEY_F))
    {
        this->flock.addForce(force);
    }
}

void Scene::pausePlayKey(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_A))
    {
        ctx.pause();
    }
    if (ctx.key_is_pressed(GLFW_KEY_S))
    {
        ctx.resume();
    }
}

void Scene::exitKey(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_Q))
    {
        ctx.stop();
    }
}