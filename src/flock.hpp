#pragma once

#include <vector>
#include "boid.hpp"
#include "glimac/sphere_vertices.hpp"
#include "p6/p6.h"

class Flock {
public:
    std::vector<Boid> flock;

    float perceptionRadius   = 0.4; // TMP for debug
    float separationDistance = 0.4; // TMP for debug

    float separationCoeff = 1.f;
    float alignmentCoeff  = 1.f;
    float cohesionCoeff   = 1.f;

public:
    Flock();
    Flock(size_t total);

    void update(p6::Context& ctx, float& wallSize, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer);
    void updateMenu();
};
