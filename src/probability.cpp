#include "probability.hpp"
#include <sys/_types/_size_t.h>
#include "binomial.hpp"

void setBoidsSize(const size_t& nbFishTotal, size_t& nbLittleFish, size_t& nbMediumFish, size_t& nbBigFish)
{
    float p = 0.5; // [0.0, 1.0] For p = 0.5 -> the distribution is balanced

    size_t nbTrialsLittleFish = 11;
    size_t nbTrialsBigFish    = 4;

    nbLittleFish = binomialDistribution(nbTrialsLittleFish, p);
    nbBigFish    = binomialDistribution(nbTrialsBigFish, p);
    nbMediumFish = nbFishTotal - (nbBigFish + nbLittleFish);
}
