#include "tools.hpp"

// Shapes

void drawSquare(p6::Context& ctx, glm::vec2 position, float side)
{
    ctx.square(
        p6::Center{position},
        p6::Radius{side}
    );
}

void drawCircle(p6::Context& ctx, glm::vec2 position, float radius)
{
    ctx.circle(
        p6::Center{position},
        p6::Radius{radius}
    );
}

// Other tools

bool isBetween(float compare, float border, float smallest, float biggest)
{
    return smallest - border <= compare && compare <= biggest + border;
}
