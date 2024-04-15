#include "flock.hpp"
#include "boid.hpp"
#include "p6/p6.h"
#include "probability.hpp"

// --- PUBLIC ---

Flock::Flock()
{
    for (size_t i = 1; i < 5 + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusLittleFish, this->radiusLittleFish + 0.5, this->radiusLittleFish, glm::vec3{0.f, 0.f, 0.f}, setFishVelocity()));
    }
}

Flock::Flock(size_t total, float wallSize)
    : nbFishTotal(total)
{
    // define number of fish per fish size
    setNbFishBySize(this->nbFishTotal, this->nbLittleFish, this->nbMediumFish, this->nbBigFish);

    for (size_t i = 1; i < this->nbLittleFish + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusLittleFish, this->radiusLittleFish + 0.6, this->radiusLittleFish, setLittleFishPosition(wallSize), setFishVelocity()));
    }
    for (size_t i = 1; i < this->nbMediumFish + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusMediumFish, this->radiusMediumFish + 0.4, this->radiusMediumFish, setMediumFishPosition(), setFishVelocity()));
    }
    for (size_t i = 1; i < this->nbBigFish + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusBigFish, this->radiusBigFish + 0.2, this->radiusBigFish, setBigFishPosition(wallSize), setFishVelocity()));
    }
}

void Flock::update(p6::Context& ctx, float& wallSize, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        this->flock[i].run(this->flock, this->separationCoeff, this->alignmentCoeff, this->cohesionCoeff, wallSize, ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, boidContainer);
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

    // ImGui::Text("Little fish: %zu", this->nbLittleFish);
    // ImGui::Text("Medium fish: %zu", this->nbMediumFish);
    // ImGui::Text("Big fish: %zu", this->nbBigFish);
}
