#include "flock.hpp"
#include "boid.hpp"
#include "loader.h"
#include "p6/p6.h"
#include "probability.hpp"
#include "texture.hpp"

// --- PUBLIC ---

Flock::Flock()
{
    for (size_t i = 1; i < 5 + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusLittleFish, this->radiusLittleFish + 0.5, this->radiusLittleFish, glm::vec3{0.f, 0.f, 0.f}, setFishVelocity(), 0.00333f));
    }
}

Flock::Flock(size_t total, float wallSize)
    : nbFishTotal(total)
{
    // define number of fish per fish size
    setNbFishBySize(this->nbFishTotal, this->nbLittleFish, this->nbMediumFish, this->nbBigFish);

    for (size_t i = 1; i < this->nbLittleFish + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusLittleFish, this->radiusLittleFish + 0.6, this->radiusLittleFish, setLittleFishPosition(wallSize), setFishVelocity(), 0.00333f));
    }
    for (size_t i = 1; i < this->nbMediumFish + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusMediumFish, this->radiusMediumFish + 0.4, this->radiusMediumFish, setMediumFishPosition(), setFishVelocity(), 0.00333f));
    }
    for (size_t i = 1; i < this->nbBigFish + 1; i++)
    {
        this->flock.push_back(Boid(this->radiusBigFish, this->radiusBigFish + 0.2, this->radiusBigFish, setBigFishPosition(wallSize), setFishVelocity(), 0.00333f));
    }
}

void Flock::update(p6::Context& ctx, float wallSize, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, Texture& texLittleFish, Texture& texMediumFish, Texture& texBigFish, const std::vector<vertex>& fishVertices)
{
    for (size_t i = 0; i < this->flock.size(); i++)
    {
        if (this->flock[i].getRadius() == this->radiusLittleFish)
        {
            texLittleFish.activate();
            texLittleFish.bind();
            this->flock[i].run(this->flock, this->separationCoeff, this->alignmentCoeff, this->cohesionCoeff, wallSize, ctx, camMVMatrix, uniMVP, uniMV, uniNormal, fishVertices);
            texLittleFish.unbind();
        }
        else if (this->flock[i].getRadius() == this->radiusMediumFish)
        {
            texMediumFish.activate();
            texMediumFish.bind();
            this->flock[i].run(this->flock, this->separationCoeff, this->alignmentCoeff, this->cohesionCoeff, wallSize, ctx, camMVMatrix, uniMVP, uniMV, uniNormal, fishVertices);
            texMediumFish.unbind();
        }
        else
        {
            texBigFish.activate();
            texBigFish.bind();
            this->flock[i].run(this->flock, this->separationCoeff, this->alignmentCoeff, this->cohesionCoeff, wallSize, ctx, camMVMatrix, uniMVP, uniMV, uniNormal, fishVertices);
            texBigFish.unbind();
        }
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
}
