#pragma once
#include "boid.hpp"
#include "loader.h"
#include "p6/p6.h"
#include "texture.hpp"

class Flock {
private:
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
    std::vector<Boid> flock;
    size_t            nbFishTotal;

public:
    Flock();
    Flock(size_t total, const float wallSize);

    void update(p6::Context& ctx, float& wallSize, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, Texture& texLittleFish, Texture& texMediumFish, Texture& texBigFish, const std::vector<vertex>& fishVertexContainer);
    void updateMenu();
};
