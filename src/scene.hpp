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
public:
    glm::vec2 position;
    Flock     flock;
    ImVec4    backgroundColor;

public:
    float side = 2.f;
    Scene()
        : position{glm::vec2{0.f, 0.f}} {};
    Scene(glm::vec2 position)
        : position{position} {};

    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<Vertex2DTex>& cubeContainer);
    void updateMenu();
    void drawMenu();

    void setBackgroundColor(float r, float g, float b);
};
