#pragma once

#include "glimac/sphere_vertices.hpp"
#include "p6/p6.h"

class Boid {
public:
    glm::vec3 position, velocity, acceleration;
    float     radius;
    float     perceptionRadius;
    float     separationDistance;
    float     maxSpeed = 0.00333;

public:
    void applyBoidsBehaviour(std::vector<Boid>& allBoids, float& separationCoeff, float& alignmentCoeff, float& cohesionCoeff);
    void update();
    void wrapAround(float& wall);
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer);

    bool      inRadius(Boid& boid, float& radius);
    glm::vec3 separate(std::vector<Boid>& allBoids);
    glm::vec3 align(std::vector<Boid>& allBoids);
    glm::vec3 cohered(std::vector<Boid>& allBoids);

    void updatePosition();
    void updateVelocity();
    void updateAcceleration(glm::vec3& force);

public:
    Boid(float radius, float perceptionRadius, float separationDistance, glm::vec3 position, glm::vec3 velocity)
        : position{position}, velocity{velocity}, acceleration{0.f, 0.f, 0.f}, radius{radius}, perceptionRadius(perceptionRadius), separationDistance(separationDistance){};

    void run(std::vector<Boid>& allBoids, float& separation, float& alignment, float& cohesion, float& wall, p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer);
};
