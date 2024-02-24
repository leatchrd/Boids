#include "scene.hpp"
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
