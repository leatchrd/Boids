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
        this->flock[i].run(this->flock, this->separationCoeff, this->alignmentCoeff, this->cohesionCoeff, this->perceptionRadius, this->separationDistance, wallSize, ctx);
    }
}

void Flock::updateMenu()
{
    ImGui::SliderFloat("Separation coefficient", &this->separationCoeff, 0.0f, 100.0f);
    ImGui::SliderFloat("Alignment coefficient", &this->alignmentCoeff, 0.0f, 100.0f);
    ImGui::SliderFloat("Cohesion coefficient", &this->cohesionCoeff, 0.0f, 100.0f);
    ImGui::Spacing();

    ImGui::SliderFloat("Perception radius", &this->perceptionRadius, 0.0f, 1.0f);
    ImGui::SliderFloat("Separation distance", &this->separationDistance, 0.0f, 1.0f);
}

// --- PRIVATE ---

void Flock::addBoid(Boid single)
{
    this->flock.push_back(single);
}
