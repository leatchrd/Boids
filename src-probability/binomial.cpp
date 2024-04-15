#include "binomial.hpp"
#include "random.hpp"

int binomialDistribution(int nbTrials, float p)
{
    int x = 0;
    for (int i = 0; i < nbTrials; ++i)
    {
        if (rand01() < p)
        {
            x++;
        }
    }
    return x + 1; // at least one fish
}
