#include "boid.hpp"
#include "p6/p6.h"
#include "tools.hpp"

Boid::Boid(float radius, glm::vec2 velocity)
    : position{0., 0.}, velocity{velocity}, acceleration{0., 0.}, separation{0.02, 0.02}, radius{radius}
{
}

// DRAW

void Boid::draw(p6::Context& ctx)
{
    drawCircle(ctx, this->position, this->radius);
}

// UPDATE

void Boid::updatePosition()
{
    this->position += this->velocity;
}

void Boid::updateVelocity()
{
    this->velocity += this->acceleration;
}

void Boid::updateAcceleration(glm::vec2& force)
{
    this->acceleration += force;
}

void Boid::update(float& wallSize)
{
    this->collisionWithWall(wallSize);

    this->updateVelocity();
    this->updatePosition();
}

// ALINEMENT

void Boid::aline(glm::vec2& target_position)
{
    this->velocity = target_position;
    // std::cout << "new velocity x = " << this->velocity.x << " - new velocity y = " << this->velocity.y << std::endl;
}

// OTHER ACTIONS

// FOR COLLISIONS

void Boid::onWall(float& wallSize)
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
            this->onWhichWall = NOTHING;
        }
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
            this->onWhichWall = NOTHING;
        }
    }
}

void Boid::collisionWithWall(float& wallSize)
{
    this->onWall(wallSize);
    if (this->onWhichWall != NOTHING)
    {
        this->bounceOnWhichWall();
    }
}

void Boid::computeNewDirectionAfterBounce(glm::vec2& norm)
{
    this->velocity.x = this->velocity.x - norm.x * 2 * glm::dot(this->velocity, norm);
    this->velocity.y = this->velocity.y - norm.y * 2 * glm::dot(this->velocity, norm);
}

void Boid::bounceOnWhichWall()
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

    this->computeNewDirectionAfterBounce(wallNorm);
}
