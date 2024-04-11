#include "flock.hpp"
#include <vector>
#include "boid.hpp"
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Flock::Flock()
{
    for (size_t i = 1; i < 5 + 1; i++)
    {
        this->flock.push_back(Boid(0.01f, glm::vec3{0.f, 0.f, 0.f}, glm::vec3{randNeg1_1(), randNeg1_1(), randNeg1_1()}));
    }
}

Flock::Flock(size_t total)
{
    for (size_t i = 1; i < total + 1; i++)
    {
        this->flock.push_back(Boid(0.01f, glm::vec3{0.f, 0.f, 0.f}, glm::vec3{randNeg1_1(), randNeg1_1(), randNeg1_1()}));
    }
}

void Flock::update(p6::Context& ctx, float& wallSize, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].run(this->flock, this->separationCoeff, this->alignmentCoeff, this->cohesionCoeff, this->perceptionRadius, this->separationDistance, wallSize, ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, boidContainer);
    }
}

void Flock::updateMenu()
{
    ImGui::Text("Separation coefficient");
    ImGui::SliderFloat("##Separation coefficient", &this->separationCoeff, 0.0f, 100.0f);
    ImGui::Text("Alignment coefficient");
    ImGui::SliderFloat("##Alignment coefficient", &this->alignmentCoeff, 0.0f, 100.0f);
    ImGui::Text("Cohesion coefficient");
    ImGui::SliderFloat("##Cohesion coefficient", &this->cohesionCoeff, 0.0f, 100.0f);

    ImGui::NewLine();

    ImGui::Text("Perception radius");
    ImGui::SliderFloat("##Perception radius", &this->perceptionRadius, 0.0f, 1.0f);
    ImGui::Text("Separation distance");
    ImGui::SliderFloat("##Separation distance", &this->separationDistance, 0.0f, 1.0f);
}
