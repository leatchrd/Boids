#pragma once
#include "3DTools.hpp"
#include "flock.hpp"
// #include "loader.h"
#include "p6/p6.h"

namespace colorsBackground {
constexpr float Red   = 0.85f;
constexpr float Green = 0.98f;
constexpr float Blue  = 0.8f;
}; // namespace colorsBackground

class Scene {
private:
    float aquariumDetailLevel;
    float side;
    Flock flock;

    ImVec4 backgroundColor;

public:
    Scene()
        : aquariumDetailLevel{1.5f}, side{2.0f} {};

    void updateMenu();

    inline float getAquariumDetailLevel() { return this->aquariumDetailLevel; };
    inline float getSide() { return this->side; };

    // void setBackgroundColor(float r, float g, float b);
};
