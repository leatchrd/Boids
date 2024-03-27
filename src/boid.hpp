#pragma once

#include "p6/p6.h"

class Boid {
private:
    glm::vec2 position, velocity, acceleration;
    float     radius;
    // float     maxDistanceToWall = 0.05;

    float maxSpeed        = 0.00333;
    float maxAcceleration = 0.00008;

private:
    void updatePosition();
    void updateVelocity();
    void updateAcceleration(glm::vec2& force);

    // void checkIfOutside(float& wall);
    void wrapAround(float& wall);
    void applyBoidsBehaviour(std::vector<Boid>& allBoids, float& separationCoeff, float& alignmentCoeff, float& cohesionCoeff, float& perceptionRadius, float& separationDistance);
    void update();
    // void avoidWalls(float& wall);
    void draw(p6::Context& ctx);

    bool      inRadius(Boid& boid, float& radius);
    glm::vec2 separate(std::vector<Boid>& allBoids, float& separationDistance);
    glm::vec2 align(std::vector<Boid>& allBoids, float& perceptionRadius);
    glm::vec2 cohered(std::vector<Boid>& allBoids, float& perceptionRadius);

    // void avoidOneWall(float& position, float& wall);

public:
    Boid(float radius, glm::vec2 position, glm::vec2 velocity);
    void run(std::vector<Boid>& allBoids, float& separation, float& alignment, float& cohesion, float& perceptionRadius, float& separationDistance, float& wall, p6::Context& ctx);
};
