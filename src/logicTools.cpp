#include "logicTools.hpp"
#include "p6/p6.h"

bool isBetween(float compare, float border, float smallest, float biggest)
{
    return smallest - border <= compare && compare <= biggest + border;
}

bool isBeyond(float compare, float border, float smallest, float biggest)
{
    return biggest < compare + border || compare - border < smallest;
}

glm::vec3 limit(glm::vec3& vector, float& max)
{
    float magnitude = glm::length(vector);
    float a         = std::min(magnitude, max) / magnitude;
    return vector *= a;
}

float randNeg1_1() // TODO: move to src-probability/random.cpp
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<float>{-1.0, 1.0};

    return distrib(gen);
}
