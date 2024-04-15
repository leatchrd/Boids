#include "random.hpp"
#include <random>

float rand01() // uniform distribution [0.0, 1.0]
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<float>{0.0, 1.0};

    return distrib(gen);
}

float randNeg1_1() // uniform distribution [-1.0, 1.0]
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<float>{-1.0, 1.0};

    return distrib(gen);
}
