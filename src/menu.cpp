#include "menu.hpp"
#include <p6/p6.h>

void Menu::createMenu(float& side)
{
    ImGui::Begin("Settings");
    ImGui::SliderFloat("Square size", &side, 0.f, 1.f);
    ImGui::End();

    // ImGui::ShowDemoWindow();
}