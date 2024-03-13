#include "menu.hpp"
#include <p6/p6.h>

void Menu::createMenu(float& side)
{
    ImGui::Begin("Settings");
    // ImGui::SliderFloat("Numbers of boids");
    ImGui::SliderFloat("Square size", &side, 0.8f, 1.0f);
    ImGui::End();

    ImGui::ShowDemoWindow();
}