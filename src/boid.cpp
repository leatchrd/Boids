#include "boid.hpp"
#include <vector>
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Boid::Boid(float radius, glm::vec3 position, glm::vec3 velocity)
    : position{position}, velocity{velocity}, acceleration{0.f, 0.f, 0.f}, radius{radius}
{
}

void Boid::run(std::vector<Boid>& allBoids, float& separation, float& alignment, float& cohesion, float& perceptionRadius, float& separationDistance, float& wall, p6::Context& ctx, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer)
{
    this->applyBoidsBehaviour(allBoids, separation, alignment, cohesion, perceptionRadius, separationDistance);
    this->update();
    this->wrapAround(wall);
    this->draw(ctx, uni_MVP, uni_MV, uni_Normal, boidContainer);
}

// --- PRIVATE ---

// NECESSARY TO RUN

void Boid::applyBoidsBehaviour(std::vector<Boid>& allBoids, float& separationCoeff, float& alignmentCoeff, float& cohesionCoeff, float& perceptionRadius, float& separationDistance)
{
    glm::vec3 separation = this->separate(allBoids, separationDistance);
    glm::vec3 alignment  = this->align(allBoids, perceptionRadius);
    glm::vec3 cohesion   = this->cohered(allBoids, perceptionRadius);

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
    glm::vec3 zero{0.f, 0.f, 0.f};
    this->updateAcceleration(zero);
}

void Boid::wrapAround(float& wall)
{
    if (this->position.x < -wall + this->radius)
    {
        this->position.x = wall - this->radius;
        // this->position.y = -this->position.y;
        // this->position.z = -this->position.z;
    }
    else if (this->position.x > wall - this->radius)
    {
        this->position.x = -wall + this->radius;
        // this->position.y = -this->position.y;
        // this->position.z = -this->position.z;
    }
    if (this->position.y < -wall + this->radius)
    {
        this->position.y = wall - this->radius;
        // this->position.x = -this->position.x;
        // this->position.z = -this->position.z;
    }
    else if (this->position.y > wall - this->radius)
    {
        this->position.y = -wall + this->radius;
        // this->position.x = -this->position.x;
        // this->position.z = -this->position.z;
    }
    if (this->position.z < -wall + this->radius)
    {
        this->position.z = wall - this->radius;
        // this->position.x = -this->position.x;
        // this->position.y = -this->position.y;
    }
    else if (this->position.z > wall - this->radius)
    {
        this->position.z = -wall + this->radius;
        // this->position.x = -this->position.x;
        // this->position.y = -this->position.y;
    }
}

void Boid::draw(p6::Context& ctx, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // adjust ojbect location
    MVMatrix = glm::translate(glm::mat4{1.f}, this->position);
    MVMatrix = glm::scale(MVMatrix, glm::vec3{this->radius});
    MVMatrix = glm::translate(MVMatrix, glm::vec3{0.f, 0.f, -1.f});

    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // draw boid
    glDrawArrays(GL_TRIANGLES, 0, boidContainer.size());
}

// FOR BOID BEHAVIOUR

bool Boid::inRadius(Boid& boid, float& radius)
{
    return glm::distance(this->position, boid.position) > 0 && glm::distance(this->position, boid.position) < radius;
}

// -- separation

glm::vec3 Boid::separate(std::vector<Boid>& allBoids, float& separationDistance)
{
    glm::vec3 newDirection{0.f, 0.f, 0.f};
    size_t    nbCloseBoids = 0;

    for (size_t i = 0; i < allBoids.size(); i++)
    {
        if (this->inRadius(allBoids[i], separationDistance) && this != &allBoids[i])
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
        // newDirection *= 10;
    }

    return newDirection;
}

// -- alignment

glm::vec3 Boid::align(std::vector<Boid>& allBoids, float& perceptionRadius)
{
    glm::vec3 avgVelocity{0.f, 0.f, 0.f};
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

glm::vec3 Boid::cohered(std::vector<Boid>& allBoids, float& perceptionRadius)
{
    glm::vec3 avgPosition{0.f, 0.f, 0.f};
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

void Boid::updateAcceleration(glm::vec3& force)
{
    this->acceleration += force;
}
