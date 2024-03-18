#pragma once

#include "boid.hpp"
#include "flock.hpp"
#include "p6/p6.h"

class Scene {
public:
    glm::vec2 position;
    Flock     flock;
    ImVec4    backgroundColor;

public:
    float side = 0.8f;
    Scene(glm::vec2 position);
    ~Scene() = default;

    void draw(p6::Context& ctx, float radius);
    void update(p6::Context& ctx);

    bool collisionWithWall(Boid& boid);

    void dealWithWallCollisions();
    void dealWithFKeyPressed(p6::Context& ctx, glm::vec2 force);
    void pausePlayKey(p6::Context& ctx);
    void exitKey(p6::Context& ctx);
    void setBackgroundColor(float r, float g, float b);
};
