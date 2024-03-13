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

float distanceBetween(glm::vec2 boid1_pos, glm::vec2 boid2_pos)
{
    return glm::sqrt(glm::pow((boid1_pos.x - boid2_pos.x), 2) + glm::pow((boid1_pos.y - boid2_pos.y), 2));
}

float rand01()
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<float>{0.0, 1.0};

    return distrib(gen);
}
