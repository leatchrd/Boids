#include "menu.hpp"
#include <p6/p6.h>
#include "scene.hpp"

void Menu::createMenu(Scene& myScene)
{
    static int selectedColor = 0; // Variable pour stocker la couleur sélectionnée

    ImGui::Begin(
        "Settings", nullptr,
        ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoMove

    );
    // ImGui::SliderFloat("Numbers of boids");

    ImGui::SliderFloat("Square size", &myScene.side, 0.8f, 1.0f);

    // Menu dans lequel on peut input le nombre de boids

    // size_t newSize = myScene.flock.flock.size;
    // ImGui::InputInt("Nombre de boids", &newSize, 5);

    // if (newSize != myScene.flock.flock.size && newSize > 0)
    // {
    //     myScene.flock.flock.size = newSize;
    // }

    // Options de couleur
    ImGui::Text("Select Background Color:");
    if (ImGui::Selectable("Color 1"))
    {
        selectedColor = 0; // L'utilisateur a sélectionné la couleur 1
    }
    if (ImGui::Selectable("Color 2"))
    {
        selectedColor = 1; // L'utilisateur a sélectionné la couleur 2
    }
    if (ImGui::Selectable("Color 3"))
    {
        selectedColor = 2; // L'utilisateur a sélectionné la couleur 3
    }

    // ImGui::ShowDemoWindow();
    ImGui::End();

    // Appel de la fonction pour mettre à jour la couleur de fond
    updateBackgroundColor(myScene, selectedColor);
}

void Menu::updateBackgroundColor(Scene& myScene, int selectedColor)
{
    switch (selectedColor)
    {
    case 0:
        myScene.setBackgroundColor(p6::hex(0xF0FBCA));
        break;
    case 1:
        myScene.setBackgroundColor(p6::hex(0xD8FBCB));
        break;
    case 2:
        myScene.setBackgroundColor(p6::hex(0xCAFBD5));
        break;
    default:
        break;
    }
}