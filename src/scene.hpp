#pragma once
#include "p6/p6.h"

class Scene {
private:
    float aquariumDetailLevel;
    float side;

public:
    Scene()
        : aquariumDetailLevel{1.5f}, side{2.0f} {};

    void updateMenu();

    inline float getAquariumDetailLevel() { return this->aquariumDetailLevel; };
    inline float getSide() { return this->side; };
};
