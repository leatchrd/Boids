#include "scene.hpp"
#include <imgui.h>
#include "3DTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "tools.hpp"

// --- PUBLIC ---

Scene::Scene()
    : position{glm::vec2{0.f, 0.f}}
{
}

Scene::Scene(glm::vec2 position)
    : position{position}
{
}

void Scene::drawSingleWall(p6::Context& ctx, float rotationAngle, glm::vec3 rotationAxis, glm::vec3 targetPosition, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, std::vector<Vertex2DTex>& wallContainer)
{
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // adjust object
    MVMatrix = glm::translate(MVMatrix, targetPosition);
    MVMatrix = glm::rotate(MVMatrix, rotationAngle, rotationAxis);

    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // draw using the VAO
    glDrawArrays(GL_TRIANGLES, 0, wallContainer.size());
}

void Scene::draw(p6::Context& ctx, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, std::vector<Vertex2DTex>& wallContainer)
{
    // background
    ctx.background(p6::rgb(colorsBackground::Red, colorsBackground::Green, colorsBackground::Blue));
    // ctx.background(backgroundColor);

    // CUBE
    // back
    this->drawSingleWall(ctx, glm::radians(0.f), glm::vec3{0.f, 1.f, 0.f}, glm::vec3{0.f, 0.f, -1.f}, uni_MVP, uni_MV, uni_Normal, wallContainer);
    // left
    this->drawSingleWall(ctx, glm::radians(90.f), glm::vec3{0.f, 1.f, 0.f}, glm::vec3{-0.5f, 0.f, -0.5f}, uni_MVP, uni_MV, uni_Normal, wallContainer);
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

void Scene::setBackgroundColor(float r, float g, float b)
{
    r = std::clamp(r, 0.0f, 1.0f);
    g = std::clamp(g, 0.0f, 1.0f);
    b = std::clamp(b, 0.0f, 1.0f);

    this->backgroundColor = ImVec4(r, g, b, 1.0f);
}
