#include "scene.hpp"
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Scene::Scene(glm::vec2 position)
    : position{position}, flock(20)
{
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

void Scene::update(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_Q))
    {
        ctx.stop();
    }

    this->flock.update(ctx, this->side);
}
