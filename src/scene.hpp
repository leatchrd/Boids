#pragma once

#include "p6/p6.h"

class Scene {
private:
    glm::vec2 position;
    float     side;

private:
    void drawSquare(p6::Context& ctx, glm::vec2 position, float side);
    void drawCircle(p6::Context& ctx, glm::vec2 position, float radius);

public:
    Scene(glm::vec2 position, float side);
    ~Scene() = default;

    void draw(p6::Context& ctx, float radius);
};
