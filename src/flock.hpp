#pragma once

#include <vector>
#include "boid.hpp"
#include "p6/p6.h"

class Flock {
public:
    std::vector<Boid> flock;

    float perceptionRadius   = 0.5; // TMP for debug
    float separationDistance = 0.5; // TMP for debug

    float separationCoeff = 1.f;
    float alignmentCoeff  = 1.f;
    float cohesionCoeff   = 1.f;

private:
    void addBoid(Boid single);

public:
    Flock(size_t total);
    void update(p6::Context& ctx, float& wallSize);
    void updateMenu();
};
