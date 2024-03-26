#pragma once

#include "p6/p6.h"

// Shapes
void drawSquare(p6::Context& ctx, glm::vec2 position, float side);
void drawCircle(p6::Context& ctx, glm::vec2 position, float radius);

// Other tools
bool      isBetween(float compare, float border, float smallest, float biggest);
bool      isBeyond(float compare, float border, float smallest, float biggest);
float     randNeg101();
glm::vec2 limit(glm::vec2& vector, float& max);
