#include "boid.hpp"
#include <vector>
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Boid::Boid(float radius, glm::vec2 velocity)
    : position{0., 0.}, velocity{velocity}, acceleration{0., 0.}, radius{radius}
{
}

void Boid::run(std::vector<Boid>& allBoids, float& wallSize)
{
    this->flock(allBoids);
    this->update();
    this->checkCollisionWithWall(wallSize);
}

// --- PRIVATE ---

// DRAW

void Boid::draw(p6::Context& ctx)
{
    drawCircle(ctx, this->position, this->radius);
}

// NECESSARY TO RUN

void Boid::flock(std::vector<Boid>& allBoids)
{
    glm::vec2 separation = this->separate(allBoids);
    glm::vec2 alignment  = this->align(allBoids);
    glm::vec2 cohesion   = this->cohered(allBoids);

    // add a weight? --> TODO maybe later

    this->updateAcceleration(separation);
    this->updateAcceleration(alignment);
    this->updateAcceleration(cohesion);
}

void Boid::update()
{
    this->updateVelocity();
    this->velocity = limit(this->velocity, this->maxSpeed);
    this->updatePosition();
    glm::vec2 zero{0.f, 0.f};
    this->updateAcceleration(zero);
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

// CHECK PARAMETERS ACTIONS

bool Boid::inRadius(Boid& boid, float& radius)
{
    return distanceBetween(this->position, boid.position) > 0 && distanceBetween(this->position, boid.position) < radius;
}

// SEPARATION

glm::vec2 Boid::separate(std::vector<Boid>& allBoids)
{
    glm::vec2 newDirection{0., 0.};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], this->separation_distance))
        {
            float     distance   = glm::distance(this->position, allBoids[i].position);
            glm::vec2 difference = this->position - allBoids[i].position;
            difference /= distance;
            newDirection += difference;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        newDirection /= nbCloseBoids;
    }

    if (newDirection.length() > 0)
    {
        newDirection *= this->maxSpeed;
        newDirection -= this->velocity;
        newDirection = limit(newDirection, this->maxAcceleration);
    }

    return newDirection;
}

// ALIGNMENT

glm::vec2 Boid::align(std::vector<Boid>& allBoids)
{
    glm::vec2 avgVelocity{0., 0.};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], this->perception_radius))
        {
            avgVelocity += allBoids[i].velocity;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        avgVelocity /= nbCloseBoids;
        avgVelocity *= this->maxSpeed;

        glm::vec2 newDirection = avgVelocity - this->velocity;
        newDirection           = limit(newDirection, this->maxAcceleration);
        return newDirection;
    }
    else
    {
        return glm::vec2{0.f, 0.f};
    }
}

// COHESION

glm::vec2 Boid::cohered(std::vector<Boid>& allBoids)
{
    glm::vec2 avgPosition{0., 0.};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], this->perception_radius))
        {
            avgPosition += allBoids[i].position;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        avgPosition /= nbCloseBoids;

        glm::vec2 target = avgPosition - this->position;
        target *= this->maxSpeed;

        glm::vec2 newDirection = target - this->velocity;
        newDirection           = limit(newDirection, this->maxAcceleration);
        return newDirection;
    }
    else
    {
        return glm::vec2{0., 0.};
    }
}

// FOR COLLISIONS

void Boid::checkCollisionWithWall(float& wallSize)
{
    this->setWallIfOutOfWindow(wallSize);
    this->setWallIfCollision(wallSize);
    if (this->onWhichWall != NOTHING)
    {
        this->computeWallBounce();
    }
}

void Boid::setWallIfCollision(float& wallSize)
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

void Boid::setWallIfOutOfWindow(float& wallSize)
{
    if (isBeyond(this->position.y, this->radius, -wallSize, wallSize))
    {
        if (this->position.y > 0)
        {
            this->position.y  = wallSize - this->radius;
            this->onWhichWall = TOP;
        }
        else
        {
            this->position.y  = -wallSize + this->radius;
            this->onWhichWall = BOTTOM;
        }
    }
    else if (isBeyond(this->position.x, this->radius, -wallSize, wallSize))
    {
        if (this->position.x > 0)
        {
            this->position.x  = wallSize - this->radius;
            this->onWhichWall = RIGHT;
        }
        else
        {
            this->position.x  = -wallSize + this->radius;
            this->onWhichWall = LEFT;
        }
    }
    else
    {
        this->onWhichWall = NOTHING;
    }
}

void Boid::computeWallBounce()
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

void Boid::computeNewDirectionAfterBounce(glm::vec2& norm)
{
    this->velocity.x = this->velocity.x - norm.x * 2 * glm::dot(this->velocity, norm);
    this->velocity.y = this->velocity.y - norm.y * 2 * glm::dot(this->velocity, norm);
}
