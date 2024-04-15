#pragma once

#include "p6/p6.h"

void      setNbFishBySize(const size_t& nbFishTotal, size_t& nbLittleFish, size_t& nbMediumFish, size_t& nbBigFish);
float     getBigFishPosition(const float& wallSize);
glm::vec3 setBigFishPosition(const float& wallSize);
