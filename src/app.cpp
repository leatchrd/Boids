#include "app.hpp"
#include "p6/p6.h"

// --- PUBLIC ---

App::App()
{
    Scene newScene;
    this->scene = newScene;
}

void App::pausePlayKey(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_A))
    {
        ctx.pause();
    }
    if (ctx.key_is_pressed(GLFW_KEY_S))
    {
        ctx.resume();
    }
}

void App::exitKey(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_Q))
    {
        ctx.stop();
    }
}

// --- PRIVATE ---

void App::update()
{
    // this->scene.update(ctx);     TODO: transform into flock update
}

void App::drawMenu()
{
    ImGui::Begin(
        "Settings", nullptr,
        ImGuiWindowFlags_NoTitleBar
        // ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove

    );
    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);

    this->scene.drawMenu();

    ImGui::PopItemWidth();
    ImGui::End();
}

void App::draw(p6::Context& ctx)
{
    this->scene.draw(ctx);
}
