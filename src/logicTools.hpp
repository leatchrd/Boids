#pragma once

#include "p6/p6.h"

bool      isBetween(float compare, float border, float smallest, float biggest);
bool      isBeyond(float compare, float border, float smallest, float biggest);
glm::vec3 limit(glm::vec3& vector, float& max);

float randNeg1_1(); // TODO: move to src-probability/random.hpp
