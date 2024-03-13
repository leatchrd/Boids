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
        // this->flock.push_back(Boid(0.03f, glm::vec2{rand01(), rand01()}));
    }
}

// DRAW

void Flock::draw(p6::Context& ctx)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].draw(ctx);
    }
}

// UPDATE

void Flock::update(p6::Context& ctx)
{
    this->checkAlinement();

    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].update();
    }

    this->draw(ctx);
}

// CHECK PARAMETERS

void Flock::checkAlinement()
{
    std::vector<Boid> closeBoids;
    glm::vec2         avg_position{0., 0.};
    for (size_t i = 1; i < this->flock.size(); i++)
    {
        if (distanceBetween(flock[i - 1].position, flock[i].position) <= flock[i - 1].perception_radius)
        {
            closeBoids.push_back(flock[i - 1]);
            avg_position += flock[i - 1].position;
        }
    }

    avg_position /= closeBoids.size();

    // std::cout << "vector size = " << closeBoids.size() << " --- avg position x = " << avg_position.x << " - avg position y = " << avg_position.y << std::endl;
    for (size_t i = 0; i < closeBoids.size(); i++)
    {
        closeBoids[i].aline(avg_position);
    }
}

// OTHER ACTIONS

void Flock::addBoid(Boid single)
{
    this->flock.push_back(single);
}
