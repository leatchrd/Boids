#pragma once

#include "boid.hpp"
#include "flock.hpp"
#include "p6/p6.h"

class Scene {
private:
    glm::vec2 position;
    float     side;

public:
    Scene(glm::vec2 position, float side);
    ~Scene() = default;

    void draw(p6::Context& ctx, float radius);

    bool collisionWithWall(Boid& boid);

    void dealWithWallCollisions(Flock& flock);
    void dealWithFKeyPressed(p6::Context& ctx, Flock& flock, glm::vec2 force);
};
