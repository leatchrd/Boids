#include "gaussian.hpp"
#include <cmath>
#include "random.hpp"

float gaussianDistribution(float average, float standardDeviation)
{
    float u1 = rand01();
    float u2 = rand01();

    float z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2.0 * M_PI * u2);
    return average + standardDeviation * z0;
}
