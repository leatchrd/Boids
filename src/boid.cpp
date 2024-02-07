#include "boid.hpp"
#include "p6/p6.h"

Boid::Boid(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
}

void Boid::update()
{
    this->position += this->velocity;
}

void Boid::draw(p6::Context& ctx)
{
    ctx.circle(
        p6::Center{this->position},
        p6::Radius{0.03f}
    );
}
