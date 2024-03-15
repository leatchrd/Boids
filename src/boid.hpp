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
    glm::vec2 position, velocity, acceleration, separation;
    float     radius;

    float          perception_radius   = 0.5;
    float          separation_distance = 0.02;
    idWallPosition onWhichWall         = NOTHING;

private:
    void updatePosition();
    void updateVelocity();
    void updateAcceleration(glm::vec2& force);

    bool              inPerceptionRadius(Boid& boid);
    std::vector<Boid> getCloseBoids(std::vector<Boid>& otherBoids, glm::vec2& avg_position);

    void aline(glm::vec2& target_position);

    void onWall(float& wallSize);
    void collisionWithWall(float& wallSize);
    void computeNewDirectionAfterBounce(glm::vec2& norm);
    void bounceOnWhichWall();

public:
    Boid(float radius, glm::vec2 velocity);

    void update(float& wallSize);

    void draw(p6::Context& ctx);

    void checkAlinement(std::vector<Boid>& otherBoids);
};
