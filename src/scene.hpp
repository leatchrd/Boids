#pragma once

#include "boid.hpp"
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
};
