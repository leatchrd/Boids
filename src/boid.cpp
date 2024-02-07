#include "boid.hpp"
#include "p6/p6.h"

Boid::Boid(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration)
{
    this->position     = position;
    this->velocity     = velocity;
    this->acceleration = acceleration;
}

void Boid::update()
{
    this->velocity += this->acceleration;
    this->position += this->velocity;
}

void Boid::draw(p6::Context& ctx)
{
    ctx.circle(
        p6::Center{this->position},
        p6::Radius{0.03f}
    );
}

void Boid::addForce(glm::vec2 force)
{
    this->acceleration += force;
}
