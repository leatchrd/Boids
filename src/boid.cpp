#include "boid.hpp"
#include <vector>
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Boid::Boid(float radius, glm::vec2 position, glm::vec2 velocity)
    : position{position}, velocity{velocity}, acceleration{0., 0.}, radius{radius}
{
}

void Boid::run(std::vector<Boid>& allBoids, float& separation, float& alignment, float& cohesion, float& perceptionRadius, float& separationDistance, float& wall, p6::Context& ctx)
{
    this->applyBoidsBehaviour(allBoids, separation, alignment, cohesion, perceptionRadius, separationDistance);
    this->update();
    this->wrapAround(wall);
    this->draw(ctx);
}

// --- PRIVATE ---

// NECESSARY TO RUN

void Boid::applyBoidsBehaviour(std::vector<Boid>& allBoids, float& separationCoeff, float& alignmentCoeff, float& cohesionCoeff, float& perceptionRadius, float& separationDistance)
{
    glm::vec2 separation = this->separate(allBoids, separationDistance);
    glm::vec2 alignment  = this->align(allBoids, perceptionRadius);
    glm::vec2 cohesion   = this->cohered(allBoids, perceptionRadius);

    // add a weights
    separation *= separationCoeff / 1000; // *= 0.008;
    alignment *= alignmentCoeff / 1000;   // *= 0.0016;
    cohesion *= cohesionCoeff / 10000;    // *= 0.00033;

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

void Boid::wrapAround(float& wall)
{
    if (this->position.x < -wall + this->radius)
    {
        this->position.x = wall - this->radius;
        this->position.y = -this->position.y;
    }
    if (this->position.y < -wall + this->radius)
    {
        this->position.y = wall - this->radius;
        this->position.x = -this->position.x;
    }
    if (this->position.x > wall - this->radius)
    {
        this->position.x = -wall + this->radius;
        this->position.y = -this->position.y;
    }
    if (this->position.y > wall - this->radius)
    {
        this->position.y = -wall + this->radius;
        this->position.x = -this->position.x;
    }
}

void Boid::draw(p6::Context& ctx)
{
    drawCircle(ctx, this->position, this->radius);
}

// FOR BOID BEHAVIOUR

bool Boid::inRadius(Boid& boid, float& radius)
{
    return glm::distance(this->position, boid.position) > 0 && glm::distance(this->position, boid.position) < radius;
}

// -- separation

glm::vec2 Boid::separate(std::vector<Boid>& allBoids, float& separationDistance)
{
    glm::vec2 newDirection{0., 0.};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], separationDistance) && this != &allBoids[i])
        {
            float     distance   = glm::distance(this->position, allBoids[i].position);
            glm::vec2 difference = this->position - allBoids[i].position;
            difference /= (distance * distance);
            newDirection += difference;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        newDirection /= nbCloseBoids;
        glm::normalize(newDirection);
        // newDirection *= 10;
    }

    return newDirection;
}

// -- alignment

glm::vec2 Boid::align(std::vector<Boid>& allBoids, float& perceptionRadius)
{
    glm::vec2 avgVelocity{0., 0.};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], perceptionRadius) && this != &allBoids[i])
        {
            avgVelocity += allBoids[i].velocity;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        avgVelocity /= nbCloseBoids;
        glm::normalize(avgVelocity);

        glm::vec2 newDirection = avgVelocity - this->velocity;
        newDirection *= 100;
        return newDirection;
    }
    else
    {
        return glm::vec2{0.f, 0.f};
    }
}

// -- cohesion

glm::vec2 Boid::cohered(std::vector<Boid>& allBoids, float& perceptionRadius)
{
    glm::vec2 avgPosition{0., 0.};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], perceptionRadius) && this != &allBoids[i])
        {
            avgPosition += allBoids[i].position;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        avgPosition /= nbCloseBoids;

        glm::vec2 target = avgPosition - this->position;
        glm::normalize(target);

        glm::vec2 newDirection = target - this->velocity;
        glm::normalize(newDirection);
        newDirection *= 100;
        return newDirection;
    }
    else
    {
        return glm::vec2{0., 0.};
    }
}

// FOR UPDATE

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
