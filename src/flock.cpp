#include "flock.hpp"
#include <vector>
#include "boid.hpp"
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Flock::Flock(size_t total)
{
    for (size_t i = 1; i < total + 1; i++)
    {
        this->flock.push_back(Boid(0.03f, glm::vec2{0.f, 0.f}, glm::vec2{randNeg101(), randNeg101()}));
    }
}

void Flock::update(p6::Context& ctx, float& wallSize)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].run(this->flock, wallSize);
    }

    this->draw(ctx);
}

// --- PRIVATE ---

void Flock::draw(p6::Context& ctx)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].draw(ctx);
    }
}

void Flock::addBoid(Boid single)
{
    this->flock.push_back(single);
}
