#include "probability.hpp"
#include "binomial.hpp"
#include "gaussian.hpp"
#include "p6/p6.h"

void setNbFishBySize(const size_t& nbFishTotal, size_t& nbLittleFish, size_t& nbMediumFish, size_t& nbBigFish)
{
    float p = 0.5; // [0.0, 1.0] For p = 0.5 -> the distribution is balanced

    size_t nbTrialsLittleFish = 11;
    size_t nbTrialsBigFish    = 4;

    nbLittleFish = binomialDistribution(nbTrialsLittleFish, p);
    nbBigFish    = binomialDistribution(nbTrialsBigFish, p);
    nbMediumFish = nbFishTotal - (nbBigFish + nbLittleFish);
}

float getBigFishPosition(const float& wallSize)
{
    return gaussianDistribution(
        0.0f,           // average position around 0
        wallSize / 3.0f // standard derivation around 1/3
    );
}

glm::vec3 setBigFishPosition(const float& wallSize)
{
    return glm::vec3{getBigFishPosition(wallSize), getBigFishPosition(wallSize), getBigFishPosition(wallSize)};
}
