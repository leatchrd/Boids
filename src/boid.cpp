#include "boid.hpp"
#include "p6/p6.h"
#include "tools.hpp"

Boid::Boid(float radius, glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration)
{
    this->radius       = radius;
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
        p6::Radius{this->radius}
    );
}

void Boid::addForce(glm::vec2 force)
{
    this->acceleration += force;
}

bool Boid::onWall(float wallSize)
{
    if (isBetween(this->position.y, -this->radius, -wallSize, wallSize))
    {
        if (this->position.x - this->radius <= -wallSize)
        {
            this->onWhichWall = LEFT;
        }
        else if (this->position.x + this->radius >= wallSize)
        {
            this->onWhichWall = RIGHT;
        }
        else
        {
            return false;
        }
        return true;
    }

    if (isBetween(this->position.x, -this->radius, -wallSize, wallSize))
    {
        if (this->position.y + this->radius >= wallSize)
        {
            this->onWhichWall = TOP;
        }
        else if (this->position.y - this->radius <= -wallSize)
        {
            this->onWhichWall = BOTTOM;
        }
        else
        {
            return false;
        }
        return true;
    }

    return false;
}

void Boid::newDirection(glm::vec2 norm)
{
    this->velocity.x = this->velocity.x - norm.x * 2 * glm::dot(this->velocity, norm);
    this->velocity.y = this->velocity.y - norm.y * 2 * glm::dot(this->velocity, norm);
}

void Boid::newDirectionWall()
{
    glm::vec2 wallNorm(0);

    switch (this->onWhichWall)
    {
    case LEFT:
        wallNorm.x = 1.f;
        wallNorm.y = 0.f;
        break;
    case RIGHT:
        wallNorm.x = -1.f;
        wallNorm.y = 0.f;
        break;
    case TOP:
        wallNorm.x = 0.f;
        wallNorm.y = -1.f;
        break;
    case BOTTOM:
        wallNorm.x = 0.f;
        wallNorm.y = 1.f;
        break;
    default:
        break;
    }

    this->newDirection(wallNorm);
}
