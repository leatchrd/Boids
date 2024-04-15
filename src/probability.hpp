#pragma once

#include "p6/p6.h"

// primary functions
void setNbFishBySize(const size_t& nbFishTotal, size_t& nbLittleFish, size_t& nbMediumFish, size_t& nbBigFish);

glm::vec3 setLittleFishPosition(const float& wallSize);
glm::vec3 setMediumFishPosition();
glm::vec3 setBigFishPosition(const float& wallSize);

glm::vec3 setFishVelocity();

// secondary functions
float getLittleFishPosition(const float& wallSize);
float getBigFishPosition(const float& wallSize);
