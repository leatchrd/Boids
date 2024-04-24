#include "app.hpp"
// #include "3DTools.hpp"
#include "flock.hpp"
// #include "loader.h"
#include "p6/p6.h"
#include "scene.hpp"
#include "texture.hpp"

// --- PUBLIC ---

App::App(size_t nbBoids)
    : totalBoids(nbBoids)
{
    Scene newScene;
    this->scene = newScene;
    Flock newFlock(this->totalBoids, this->scene.getSide());
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

    this->scene.updateMenu();

    ImGui::PopItemWidth();
    ImGui::End();
}

void App::checkWindowQueries(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_Q)) // quit window
    {
        ctx.stop();
    }
    if (ctx.key_is_pressed(GLFW_KEY_Z)) // pause window
    {
        ctx.pause();
    }
    if (ctx.key_is_pressed(GLFW_KEY_X)) // resume window
    {
        ctx.resume();
    }
}

void App::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, Texture& texLittleFish, Texture& texMediumFish, Texture& texBigFish, Texture& texSub, Texture& texCoral1, Texture& texCoral2, Texture& texCoral3, Texture& texSeaweed1, Texture& texSeaweed2, Texture& texCube)
{
    // FISH
    this->fishModel.vao.bind();
    this->flock.update(ctx, this->scene.getSide(), camMVMatrix, uni_MVP, uni_MV, uni_Normal, texLittleFish, texMediumFish, texBigFish, this->fishModel.getObjectVertices());
    this->fishModel.vao.unbind();

    // SUBMARINE
    this->submarineModel.vao.bind();
    texSub.bind();
    this->submarineModel.update(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, this->scene.getSide());
    texSub.unbind();
    this->submarineModel.vao.unbind();

    // CORALs
    this->coralModel.vao.bind();
    this->coralModel.update(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, texCoral1, texCoral2, texCoral3);
    this->coralModel.vao.unbind();

    // SEAWEEDs
    this->seaweedModel.vao.bind();
    this->seaweedModel.update(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, texSeaweed1, texSeaweed2);
    this->seaweedModel.vao.unbind();

    // CUBE
    this->cubeModel.vao.bind();
    texCube.bind();
    this->cubeModel.draw(ctx, camMVMatrix, uni_MVP, uni_MV, uni_Normal, this->scene.getSide());
    texCube.unbind();
    this->cubeModel.vao.unbind();
}
