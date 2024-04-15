#include "app.hpp"
#include "3DTools.hpp"
#include "flock.hpp"
// #include "loader.h"
#include "p6/p6.h"
#include "scene.hpp"

// --- PUBLIC ---

App::App(size_t nbBoids)
    : totalBoids(nbBoids)
{
    Scene newScene;
    this->scene = newScene;
    Flock newFlock(this->totalBoids, this->scene.side);
    this->flock = newFlock;
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

void App::checkEvents(p6::Context& ctx)
{
    this->exitKey(ctx);
    this->pausePlayKey(ctx);
}

void App::updateFlock(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer)
{
    this->flock.update(ctx, this->scene.side, camMVMatrix, uni_MVP, uni_MV, uni_Normal, boidContainer); // TODO: transform into flock update
}

void App::drawScene(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<Vertex2DTex>& cubeContainer)
{
    this->scene.draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, cubeContainer);
}

// --- PRIVATE ---

void App::pausePlayKey(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_Z))
    {
        ctx.pause();
    }
    if (ctx.key_is_pressed(GLFW_KEY_X))
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
