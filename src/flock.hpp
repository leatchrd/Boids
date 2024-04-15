#pragma once

#include <sys/_types/_size_t.h>
#include <vector>
#include "boid.hpp"
#include "glimac/sphere_vertices.hpp"
#include "p6/p6.h"

class Flock {
public:
    std::vector<Boid> flock;

    size_t nbFishTotal;
    size_t nbLittleFish = 0;
    size_t nbMediumFish = 0;
    size_t nbBigFish    = 0;

    float radiusLittleFish = 0.1;
    float radiusMediumFish = 0.2;
    float radiusBigFish    = 0.4;

    float separationCoeff = 1.f;
    float alignmentCoeff  = 1.f;
    float cohesionCoeff   = 1.f;

public:
    Flock();
    Flock(size_t total);

    void update(p6::Context& ctx, float& wallSize, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer);
    void updateMenu();
};
