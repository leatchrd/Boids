#pragma once
#include "3DObjectTools.hpp"
#include "ibo.hpp"
#include "vao.hpp"
#include "vbo.hpp"

class Cube {
private:
    const std::vector<Vertex2DTex> cube = createCubeVertices();

public:
    VBO vbo;
    VAO vao;
    IBO ibo;

public:
    Cube();
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, float sideSize);
};
