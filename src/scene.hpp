#pragma once

#include "boid.hpp"
#include "p6/p6.h"

class Scene {
private:
    glm::vec2 position;

public:
    float side = 0.8f;
    Scene(glm::vec2 position);
    ~Scene() = default;

    void draw(p6::Context& ctx, float radius);

    bool collisionWithWall(Boid& boid);
};
