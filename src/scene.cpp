#include "scene.hpp"
#include <imgui.h>
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Scene::Scene()
    : position{glm::vec2{0.f, 0.f}}, flock(20)
{
}

Scene::Scene(glm::vec2 position)
    : position{position}, flock(20)
{
}

void Scene::draw(p6::Context& ctx)
{
    // background
    ctx.background(p6::rgb(colorsBackground::Red, colorsBackground::Green, colorsBackground::Blue));

    // cube
    drawSquare(ctx, this->position, this->side);
    // circle that follows mouse
    // drawCircle(ctx, ctx.mouse(), radius);
}

void Scene::updateMenu()
{
    ImGui::Text("Square size");
    ImGui::SliderFloat("##Square size", &this->side, 0.5f, 1.0f);
}

void Scene::drawMenu()
{
    this->updateMenu();
    ImGui::NewLine();

    this->flock.updateMenu();
}

void Scene::update(p6::Context& ctx)
{
    this->flock.update(ctx, this->side);
}

// Cette fonction ne sert à rien (pour l'instant ?)
void Scene::setBackgroundColor(float r, float g, float b)
{
    r = std::clamp(r, 0.0f, 1.0f);
    g = std::clamp(g, 0.0f, 1.0f);
    b = std::clamp(b, 0.0f, 1.0f);

    this->backgroundColor = ImVec4(r, g, b, 1.0f);
}
