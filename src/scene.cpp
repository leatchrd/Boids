#include "scene.hpp"
#include <imgui.h>
#include <vector>
#include "3DTools.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
// #include "loader.h"
#include "p6/p6.h"

// --- PUBLIC ---

void Scene::draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<Vertex2DTex>& cubeContainer)
{
    // background
    ctx.background(p6::rgb(colorsBackground::Red, colorsBackground::Green, colorsBackground::Blue));

    // CUBE
    // matrix creation
    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
    glm::mat4 MVMatrix     = glm::translate(camMVMatrix, glm::vec3(0.f, 0.f, 0.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // adjust object
    MVMatrix = glm::scale(MVMatrix, glm::vec3{2.f, 2.f, 2.f});

    // fill matrices with uniform location
    glUniformMatrix4fv(uni_MVP, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uni_MV, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uni_Normal, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // draw using the VAO
    glDrawArrays(GL_TRIANGLES, 0, cubeContainer.size());
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

// Cette fonction ne sert à rien (pour l'instant ?)
// void Scene::setBackgroundColor(float r, float g, float b)
// {
//     r = std::clamp(r, 0.0f, 1.0f);
//     g = std::clamp(g, 0.0f, 1.0f);
//     b = std::clamp(b, 0.0f, 1.0f);

//     this->backgroundColor = ImVec4(r, g, b, 1.0f);
// }
