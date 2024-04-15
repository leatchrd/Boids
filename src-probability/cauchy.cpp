#include "cauchy.hpp"
#include "random.hpp"

float cauchyDistribution(float x0, float gamma)
{
    float u = rand01();

    return x0 + gamma * std::tan(M_PI * (u - 0.5));
}
