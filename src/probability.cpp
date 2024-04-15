#include "probability.hpp"
#include "p6/p6.h"
#include "probabilityDistributions.hpp"
#include "random.hpp"

// primary functions

void setNbFishBySize(const size_t& nbFishTotal, size_t& nbLittleFish, size_t& nbMediumFish, size_t& nbBigFish)
{
    float p = 0.5; // [0.0, 1.0] For p = 0.5 -> the distribution is balanced

    size_t nbTrialsMediumFish = 11;
    size_t nbTrialsBigFish    = 4;

    nbMediumFish = binomialDistribution(nbTrialsMediumFish, p);
    nbBigFish    = binomialDistribution(nbTrialsBigFish, p);
    nbLittleFish = nbFishTotal - (nbMediumFish + nbBigFish);
}

glm::vec3 setLittleFishPosition(const float& wallSize)
{
    return glm::vec3{getLittleFishPosition(wallSize), getLittleFishPosition(wallSize), getLittleFishPosition(wallSize)};
}

glm::vec3 setMediumFishPosition()
{
    return glm::vec3{randNeg1_1(), randNeg1_1(), randNeg1_1()};
}

glm::vec3 setBigFishPosition(const float& wallSize)
{
    return glm::vec3{getBigFishPosition(wallSize), getBigFishPosition(wallSize), getBigFishPosition(wallSize)};
}

glm::vec3 setFishVelocity()
{
    float x0    = 0.f;  // distribution median
    float gamma = 1.0f; // distribution width

    return glm::vec3{cauchyDistribution(x0, gamma), cauchyDistribution(x0, gamma), cauchyDistribution(x0, gamma)};
}

// secondary functions

float getLittleFishPosition(const float& wallSize)
{
    float alpha = 0.1f;
    float beta  = 0.1f;
    // To get a hyperbole, alpha and beta should be close to 0

    return wallSize * betaDistribution(alpha, beta);
}

float getBigFishPosition(const float& wallSize)
{
    return gaussianDistribution(
        0.0f,           // average position around 0
        wallSize / 3.0f // standard derivation around 1/3
    );
}
