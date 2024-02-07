#include "scene.hpp"
#include "p6/p6.h"

// PRIVATE

void Scene::drawSquare(p6::Context& ctx, glm::vec2 position, float side)
{
    ctx.square(
        p6::Center{position},
        p6::Radius{side}
    );
}

void Scene::drawCircle(p6::Context& ctx, glm::vec2 position, float radius)
{
    ctx.circle(
        p6::Center{position},
        p6::Radius{radius}
    );
}

// PUBLIC

void Scene::draw(p6::Context& ctx, glm::vec2 position, float side, float radius)
{
    // background
    ctx.background(p6::NamedColor::Blue);
    // cube
    this->drawSquare(ctx, position, side);
    // circle that follows mouse
    this->drawCircle(ctx, ctx.mouse(), radius);
}
