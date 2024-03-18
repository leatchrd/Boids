#pragma once

#include <p6/p6.h>
#include "scene.hpp"

class Menu {
public:
    void createMenu(Scene& myScene);
    void updateBackgroundColor(Scene& myScene, int selectedColor);
};

namespace colorsBackground {
    constexpr float Red = 0.85f;
    constexpr float Green = 0.98f; 
    constexpr float Blue = 0.8f;
};