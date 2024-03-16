#pragma once

#include "p6/p6.h"

enum idWallPosition {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    NOTHING
};

class Boid {
private:
    glm::vec2 position, velocity, acceleration;
    float     radius;

    float perception_radius   = 0.3;
    float separation_distance = 0.08;
    float maxSpeed            = 0.015;
    float maxAcceleration     = 0.000005;

    idWallPosition onWhichWall = NOTHING;

private:
    void updatePosition();
    void updateVelocity();
    void updateAcceleration(glm::vec2& force);

    void update();
    void flock(std::vector<Boid>& allBoids);

    bool inPerceptionRadius(Boid& boid);
    bool inSeparationRadius(Boid& boid);

    glm::vec2 separate(std::vector<Boid>& allBoids);
    glm::vec2 align(std::vector<Boid>& allBoids);
    glm::vec2 cohered(std::vector<Boid>& allBoids);

    void checkCollisionWithWall(float& wallSize);
    void setWallIfCollision(float& wallSize);
    void setWallIfOutOfWindow(float& wallSize);
    void computeWallBounce();
    void computeNewDirectionAfterBounce(glm::vec2& norm);

public:
    Boid(float radius, glm::vec2 velocity);
    void run(std::vector<Boid>& allBoids, float& wallSize);

    void draw(p6::Context& ctx);
};
