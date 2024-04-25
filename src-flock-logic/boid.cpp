#include "boid.hpp"
#include "3DObjectTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "loader.h"
#include "logicTools.hpp"
#include "p6/p6.h"

// --- PUBLIC ---

void Boid::run(std::vector<Boid>& allBoids, float& separation, float& alignment, float& cohesion, float& wallSideSize, p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, const std::vector<vertex>& fishVertices)
{
    this->applyBoidsBehaviour(allBoids, separation, alignment, cohesion);
    this->update();
    this->wrapAround(wallSideSize);
    this->draw(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, fishVertices);
}

// --- PRIVATE ---

// NECESSARY TO RUN

void Boid::applyBoidsBehaviour(std::vector<Boid>& allBoids, float& separationCoeff, float& alignmentCoeff, float& cohesionCoeff)
{
    glm::vec3 separation = this->separate(allBoids);
    glm::vec3 alignment  = this->align(allBoids);
    glm::vec3 cohesion   = this->cohered(allBoids);

    // add a weights
    separation *= separationCoeff / 1000;
    alignment *= alignmentCoeff / 1000;
    cohesion *= cohesionCoeff / 10000;

    this->updateAcceleration(separation);
    this->updateAcceleration(alignment);
    this->updateAcceleration(cohesion);
}

void Boid::update()
{
    this->updateVelocity();
    this->velocity = limit(this->velocity, this->maxSpeed);
    this->updatePosition();
    glm::vec3 zero{0.f, 0.f, 0.f};
    this->updateAcceleration(zero);
}

void Boid::wrapAround(float wallSideSize)
{
    if (this->position.x < -wallSideSize + (this->radius * 2.5))
    {
        this->position.x = wallSideSize - (this->radius * 2.5);
    }
    else if (this->position.x > wallSideSize - (this->radius * 2.5))
    {
        this->position.x = -wallSideSize + (this->radius * 2.5);
    }
    if (this->position.y < -wallSideSize + (this->radius * 2.5))
    {
        this->position.y = wallSideSize - (this->radius * 2.5);
    }
    else if (this->position.y > wallSideSize - (this->radius * 2.5))
    {
        this->position.y = -wallSideSize + (this->radius * 2.5);
    }
    if (this->position.z < -wallSideSize + (this->radius * 2.5))
    {
        this->position.z = wallSideSize - (this->radius * 2.5);
    }
    else if (this->position.z > wallSideSize - (this->radius * 2.5))
    {
        this->position.z = -wallSideSize + (this->radius * 2.5);
    }
}

void Boid::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, const std::vector<vertex>& fishVertices)
{
    float     angle{glm::angle(glm::vec3{0.0f, 0.0f, 1.0f}, glm::normalize(this->velocity))};
    glm::vec3 axis{glm::cross(glm::vec3{0.0f, 0.0f, 1.0f}, glm::normalize(this->velocity))};

    drawMesh(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, this->position, angle, axis, this->radius, fishVertices);
}

// FOR BOID BEHAVIOUR

bool Boid::inRadius(Boid boid, float radius)
{
    return glm::distance(this->position, boid.position) > 0 && glm::distance(this->position, boid.position) < radius;
}

// -- separation

glm::vec3 Boid::separate(std::vector<Boid>& allBoids)
{
    glm::vec3 newDirection{0.f, 0.f, 0.f};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], this->separationDistance) && this != &allBoids[i])
        {
            float     distance   = glm::distance(this->position, allBoids[i].position);
            glm::vec3 difference = this->position - allBoids[i].position;
            difference /= (distance * distance);
            newDirection += difference;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        newDirection /= nbCloseBoids;
        glm::normalize(newDirection);
    }

    return newDirection;
}

// -- alignment

glm::vec3 Boid::align(std::vector<Boid>& allBoids)
{
    glm::vec3 avgVelocity{0.f, 0.f, 0.f};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], this->perceptionRadius) && this != &allBoids[i])
        {
            avgVelocity += allBoids[i].velocity;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        avgVelocity /= nbCloseBoids;
        glm::normalize(avgVelocity);

        glm::vec3 newDirection = avgVelocity - this->velocity;
        newDirection *= 100;
        return newDirection;
    }
    else
    {
        return glm::vec3{0.f, 0.f, 0.f};
    }
}

// -- cohesion

glm::vec3 Boid::cohered(std::vector<Boid>& allBoids)
{
    glm::vec3 avgPosition{0.f, 0.f, 0.f};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], this->perceptionRadius) && this != &allBoids[i])
        {
            avgPosition += allBoids[i].position;
            nbCloseBoids++;
        }
    }

    if (nbCloseBoids > 0)
    {
        avgPosition /= nbCloseBoids;

        glm::vec3 target = avgPosition - this->position;
        glm::normalize(target);

        glm::vec3 newDirection = target - this->velocity;
        glm::normalize(newDirection);
        newDirection *= 100;
        return newDirection;
    }
    else
    {
        return glm::vec3{0.f, 0.f, 0.f};
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

void Boid::updateAcceleration(glm::vec3 force)
{
    this->acceleration += force;
}
