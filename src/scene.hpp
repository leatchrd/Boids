#pragma once

#include "p6/p6.h"

class Scene {
private:
    void drawSquare(p6::Context& ctx, glm::vec2 position, float side);
    void drawCircle(p6::Context& ctx, glm::vec2 position, float radius);

public:
    void draw(p6::Context& ctx, glm::vec2 position, float side, float radius);
};
