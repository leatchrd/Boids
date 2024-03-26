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

bool isBeyond(float compare, float border, float smallest, float biggest)
{
    return biggest < compare + border || compare - border < smallest;
}

float randNeg101()
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<float>{-1.0, 1.0};

    return distrib(gen);
}

glm::vec2 limit(glm::vec2& vector, float& max)
{
    float magnitude = glm::length(vector);
    float a         = std::min(magnitude, max) / magnitude;
    return vector *= a;
}
