#include "scene.hpp"
#include "p6/p6.h"

// --- PUBLIC ---

void Scene::updateMenu()
{
    ImGui::Text("Aquarium detail level");
    ImGui::SliderFloat("##Aquarium detail level", &this->aquariumDetailLevel, 0.001f, 5.0f);

    ImGui::NewLine();
}
