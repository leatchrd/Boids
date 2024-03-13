#include "menu.hpp"
#include <p6/p6.h>
#include "scene.hpp"

void Menu::createMenu(Scene& myScene)
{
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

    ImGui::End();

    ImGui::ShowDemoWindow();
}