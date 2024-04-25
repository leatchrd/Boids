#pragma once
#include "p6/p6.h"

class Scene {
private:
    float aquariumDetailLevel;
    float sideSize;

public:
    Scene()
        : aquariumDetailLevel{1.5f}, sideSize{2.0f} {};

    void updateMenu();

    inline float getAquariumDetailLevel() { return this->aquariumDetailLevel; };
    inline float getSideSize() { return this->sideSize; };
};
