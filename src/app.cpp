#include "app.hpp"
#include "flock.hpp"
#include "p6/p6.h"
#include "scene.hpp"
#include "texture.hpp"

// --- PUBLIC ---

App::App(size_t nbBoids)
    : totalBoids(nbBoids)
{
    Scene newScene;
    this->scene = newScene;
    Flock newFlock(this->totalBoids, this->scene.getSideSize());
    this->flock = newFlock;
}

void App::drawMenu()
{
    ImGui::Begin(
        "Settings", nullptr,
        ImGuiWindowFlags_NoTitleBar
    );
    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);

    this->scene.updateMenu();
    this->flock.updateMenu();

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

void App::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, Texture& texLittleFish, Texture& texMediumFish, Texture& texBigFish, Texture& texSub, Texture& texCoral1, Texture& texCoral2, Texture& texCoral3, Texture& texSeaweed1, Texture& texSeaweed2, Texture& texCube)
{
    // FISH
    this->fishModel.vao.bind();
    this->flock.update(ctx, this->scene.getSideSize(), camMVMatrix, uniMVP, uniMV, uniNormal, texLittleFish, texMediumFish, texBigFish, this->fishModel.getObjectVertices());
    this->fishModel.vao.unbind();

    // SUBMARINE
    this->submarineModel.vao.bind();
    texSub.bind();
    this->submarineModel.update(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, this->scene.getSideSize());
    texSub.unbind();
    this->submarineModel.vao.unbind();

    // CORALs
    this->coralModel.vao.bind();
    this->coralModel.update(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, texCoral1, texCoral2, texCoral3);
    this->coralModel.vao.unbind();

    // SEAWEEDs
    this->seaweedModel.vao.bind();
    this->seaweedModel.update(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, texSeaweed1, texSeaweed2);
    this->seaweedModel.vao.unbind();

    // CUBE
    this->cubeModel.vao.bind();
    texCube.bind();
    this->cubeModel.draw(ctx, camMVMatrix, uniMVP, uniMV, uniNormal, this->scene.getSideSize());
    texCube.unbind();
    this->cubeModel.vao.unbind();
}
