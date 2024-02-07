#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
private:
    glm::vec2 position, velocity, acceleration;

public:
    Boid(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration);
    ~Boid() = default;

    void update();
    void draw(p6::Context& ctx);

    void addForce(glm::vec2 force);
};
