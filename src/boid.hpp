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
public:
    glm::vec2 position, velocity, acceleration, separation;
    float     radius;

    float          perception_radius   = 0.5;
    float          separation_distance = 0.02;
    idWallPosition onWhichWall         = NOTHING;

public:
    Boid(float radius, glm::vec2 velocity);

    void draw(p6::Context& ctx);

    void updatePosition();
    void updateVelocity();
    void updateAcceleration(glm::vec2& force);
    void update();

    void aline(glm::vec2& target_position);

    bool onWall(float wallSize);
    void newDirection(glm::vec2 norm);
    void newDirectionWall();
};
