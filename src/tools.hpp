#pragma once

#include "p6/p6.h"

// Shapes
void drawSquare(p6::Context& ctx, glm::vec2 position, float side);
void drawCircle(p6::Context& ctx, glm::vec2 position, float radius);

// Other tools
bool isBetween(float compare, float border, float smallest, float biggest);
