#include "scene.hpp"
#include "3DTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
// #include "loader.h"
#include "p6/p6.h"

// --- PUBLIC ---

void Scene::updateMenu()
{
    ImGui::Text("Aquarium detail level");
    ImGui::SliderFloat("##Aquarium detail level", &this->aquariumDetailLevel, 0.001f, 3.0f);

    ImGui::NewLine();

    this->flock.updateMenu();
}

// Cette fonction ne sert à rien (pour l'instant ?)
// void Scene::setBackgroundColor(float r, float g, float b)
// {
//     r = std::clamp(r, 0.0f, 1.0f);
//     g = std::clamp(g, 0.0f, 1.0f);
//     b = std::clamp(b, 0.0f, 1.0f);

//     this->backgroundColor = ImVec4(r, g, b, 1.0f);
// }

// background
// ctx.background(p6::rgb(colorsBackground::Red, colorsBackground::Green, colorsBackground::Blue));
