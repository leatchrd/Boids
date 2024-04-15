#include "beta.hpp"
#include "random.hpp"

float betaDistribution(float alpha, float beta)
{
    float u1 = rand01();
    float u2 = rand01();

    return pow(u1, alpha) * pow(u2, beta);
}
