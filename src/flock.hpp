#pragma once

#include <cstddef>
#include <vector>
#include "boid.hpp"
#include "p6/p6.h"

class Flock {
public:
    std::vector<Boid> flock;

private:
    void draw(p6::Context& ctx);
    void addBoid(Boid single);
    void checkAlinement();

public:
    Flock(size_t total);

    void update(p6::Context& ctx);
    void addForce(glm::vec2 force);
};
