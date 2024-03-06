#include "flock.hpp"
#include <cstddef>
#include "boid.hpp"
#include "p6/p6.h"

Flock::Flock(size_t total)
{
    for (size_t i = 1; i < total + 1; i++)
    {
        this->flock.push_back(Boid(0.03f, glm::vec2{0.f, 0.f}, glm::vec2{0.001 * i, 0.002 * i * 2}, glm::vec2{0.0, 0.0}));
    }
}

void Flock::addBoid(Boid single)
{
    this->flock.push_back(single);
}

void Flock::draw(p6::Context& ctx)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].draw(ctx);
    }
}

void Flock::addForce(glm::vec2 force)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].addForce(force);
    }
}

void Flock::update(p6::Context& ctx)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].update();
    }

    this->draw(ctx);
}
