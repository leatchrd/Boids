#pragma once
#include "3DObjectTools.hpp"
#include "vao.hpp"
#include "vbo.hpp"

class Cube {
private:
    const std::vector<Vertex2DTex> cube = createCubeVertices();

public:
    VBO vbo;
    VAO vao;

public:
    Cube();
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, float side);
};
