#pragma once
#include "loader.h"
#include "p6/p6.h"

class Boid {
private:
    glm::vec3 position, velocity, acceleration;
    float     radius;
    float     perceptionRadius;
    float     separationDistance;
    float     maxSpeed;

private:
    void applyBoidsBehaviour(std::vector<Boid>& allBoids, float& separationCoeff, float& alignmentCoeff, float& cohesionCoeff);
    void update();
    void wrapAround(float& wall);
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<vertex>& fishVertexContainer);

    bool      inRadius(Boid& boid, float& radius);
    glm::vec3 separate(std::vector<Boid>& allBoids);
    glm::vec3 align(std::vector<Boid>& allBoids);
    glm::vec3 cohered(std::vector<Boid>& allBoids);

    void updatePosition();
    void updateVelocity();
    void updateAcceleration(glm::vec3& force);

public:
    Boid(float radius, float perceptionRadius, float separationDistance, glm::vec3 position, glm::vec3 velocity, float maxSpeed)
        : position{position}, velocity{velocity}, acceleration{0.f, 0.f, 0.f}, radius{radius}, perceptionRadius(perceptionRadius), separationDistance(separationDistance), maxSpeed{maxSpeed} {};

    void run(std::vector<Boid>& allBoids, float& separation, float& alignment, float& cohesion, float& wall, p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<vertex>& fishVertexContainer);

    inline float getRadius() { return this->radius; };
};
