#pragma once
#include "loader.h"
#include "p6/p6.h"

class Vertex2DTex {
public:
    glm::vec3 position, norm;
    glm::vec2 texture;

    Vertex2DTex(glm::vec3 position, glm::vec3 norm, glm::vec2 texture)
        : position{position}, norm{norm}, texture{texture} {};
};

std::vector<Vertex2DTex> createCubeVertices();

// for OBJ mesh
void drawMesh(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, glm::vec3 position, float angle, glm::vec3 axis, float scale, const std::vector<vertex>& vertices);
// // for handmade OpenGL mesh
void drawMesh(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, glm::vec3 position, float angle, glm::vec3 axis, float scale, const std::vector<Vertex2DTex>& vertices);
