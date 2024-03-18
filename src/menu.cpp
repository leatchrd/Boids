#include "menu.hpp"
#include <p6/p6.h>
#include "scene.hpp"

void Scene::setBackgroundColor(float r, float g, float b)
{
    r = std::clamp(r, 0.0f, 1.0f);
    g = std::clamp(g, 0.0f, 1.0f);
    b = std::clamp(b, 0.0f, 1.0f);

    backgroundColor = ImVec4(r, g, b, 1.0f);
}

void Menu::createMenu(Scene& myScene)
{
    ImGui::Begin(
        "Settings", nullptr,
        ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoMove

    );

    ImGui::SliderFloat("Square size", &myScene.side, 0.8f, 1.0f);

    ImGui::Spacing();

    if (ImGui::Button("Mix green blue"))
    {
        setBackgroundColor(0.79f, 0.98f, 0.84f)
    }

    ImGui::SameLine();

    if (ImGui::Button("Yellow"))
    {
        setBackgroundColor(0.94f, 0.98f, 0.79f)
    }

    ImGui::SameLine();

    if (ImGui::Button("Apple green"))
    {
        setBackgroundColor(0.85f, 0.98f, 0.8f))
    }

    ImGui::End();

    // ImGui::ShowDemoWindow();
}