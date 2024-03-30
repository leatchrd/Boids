#pragma once

#include "flock.hpp"
#include "p6/p6.h"

namespace colorsBackground {
constexpr float Red   = 0.85f;
constexpr float Green = 0.98f;
constexpr float Blue  = 0.8f;
}; // namespace colorsBackground

class Scene {
public:
    glm::vec2 position;
    Flock     flock;
    ImVec4    backgroundColor;

public:
    float side = 0.8f;
    Scene();
    Scene(glm::vec2 position);

    void draw(p6::Context& ctx);
    void updateMenu();
    void drawMenu();

    void setBackgroundColor(float r, float g, float b);
};
