#include "boid.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "loader.h"
#include "logicTools.hpp"
#include "p6/p6.h"

// --- PUBLIC ---

void Boid::run(std::vector<Boid>& allBoids, float& separation, float& alignment, float& cohesion, float& wall, p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<vertex>& fishVertexContainer)
{
    this->applyBoidsBehaviour(allBoids, separation, alignment, cohesion);
    this->update();
    this->wrapAround(wall);
    this->draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, fishVertexContainer);
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

void Boid::wrapAround(float& wall)
{
    if (this->position.x < -wall + (this->radius * 2.5))
    {
        this->position.x = wall - (this->radius * 2.5);
    }
    else if (this->position.x > wall - (this->radius * 2.5))
    {
        this->position.x = -wall + (this->radius * 2.5);
    }
    if (this->position.y < -wall + (this->radius * 2.5))
    {
        this->position.y = wall - (this->radius * 2.5);
    }
    else if (this->position.y > wall - (this->radius * 2.5))
    {
        this->position.y = -wall + (this->radius * 2.5);
    }
    if (this->position.z < -wall + (this->radius * 2.5))
    {
        this->position.z = wall - (this->radius * 2.5);
    }
    else if (this->position.z > wall - (this->radius * 2.5))
    {
        this->position.z = -wall + (this->radius * 2.5);
    }
}

void Boid::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<vertex>& fishVertexContainer)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, this->position);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // adjust ojbect
    MVMatrix = glm::rotate(MVMatrix, glm::angle(glm::vec3{0.0f, 0.0f, 1.0f}, glm::normalize(this->velocity)), glm::cross(glm::vec3{0.0f, 0.0f, 1.0f}, glm::normalize(this->velocity)));
    MVMatrix = glm::scale(MVMatrix, glm::vec3{this->radius});

    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // draw boid
    glDrawArrays(GL_TRIANGLES, 0, fishVertexContainer.size());
}

// FOR BOID BEHAVIOUR

bool Boid::inRadius(Boid& boid, float& radius)
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

void Boid::updateAcceleration(glm::vec3& force)
{
    this->acceleration += force;
}
