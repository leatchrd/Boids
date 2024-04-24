#define _USE_MATH_DEFINES
#include "probabilityDistributions.hpp"
#include <cmath>
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

float betaDistribution(float alpha, float beta)
{
    float u1 = rand01();
    float u2 = rand01();

    return std::pow(u1, alpha) * std::pow(u2, beta);
}

float gaussianDistribution(float average, float standardDeviation)
{
    float u1 = rand01();
    float u2 = rand01();

    float z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * M_PI * u2);
    return average + standardDeviation * z0;
}

float cauchyDistribution(float x0, float gamma)
{
    float u = rand01();

    return x0 + gamma * std::tan(M_PI * (u - 0.5));
}
