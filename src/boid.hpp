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
    glm::vec2      position, velocity, acceleration;
    float          radius;
    idWallPosition onWhichWall = NOTHING;

public:
    Boid(float radius, glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration);
    ~Boid() = default;

    void update();
    void draw(p6::Context& ctx);

    void addForce(glm::vec2 force);

    bool onWall(float wallSize);

    void newDirection(glm::vec2 norm);
    void newDirectionWall();
};
