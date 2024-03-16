#include "flock.hpp"
#include <cstddef>
#include <vector>
#include "boid.hpp"
#include "p6/p6.h"
#include "tools.hpp"

Flock::Flock(size_t total)
{
    for (size_t i = 1; i < total + 1; i++)
    {
        this->flock.push_back(Boid(0.03f, glm::vec2{0.001 * i, 0.002 * i * 2}));
    }
}

// UPDATE

void Flock::update(p6::Context& ctx, float& wallSize)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].run(this->flock, wallSize);
    }

    this->draw(ctx);
}

// DRAW

void Flock::draw(p6::Context& ctx)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].draw(ctx);
    }
}

// OTHER ACTIONS

void Flock::addBoid(Boid single)
{
    this->flock.push_back(single);
}
