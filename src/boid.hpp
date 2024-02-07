#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
private:
    glm::vec2 position, velocity;

public:
    Boid(glm::vec2 position, glm::vec2 velocity);
    ~Boid() = default;

    void update();
    void draw(p6::Context& ctx);
};
