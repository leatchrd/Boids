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

glm::vec3 limit(glm::vec3 vector, float max)
{
    float magnitude = glm::length(vector);
    float a         = std::min(magnitude, max) / magnitude;
    return vector *= a;
}
