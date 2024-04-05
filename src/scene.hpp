#pragma once

#include "3DTools.hpp"
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
    float side = 0.5f;
    Scene();
    Scene(glm::vec2 position);

    void drawSingleWall(p6::Context& ctx, float rotationAngle, glm::vec3 rotationAxis, glm::vec3 targetPosition, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, std::vector<Vertex2DTex>& wallContainer);
    void draw(p6::Context& ctx, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, std::vector<Vertex2DTex>& wallContainer);
    void updateMenu();
    void drawMenu();

    void setBackgroundColor(float r, float g, float b);
};
