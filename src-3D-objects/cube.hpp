#pragma once
#include "3DTools.hpp"
// #include "loader.h"
#include "vao.hpp"
#include "vbo.hpp"

class Cube {
private:
    const std::vector<Vertex2DTex> cube = createCubeVertices();
    // const Object3D cube = loadOBJ("assets/models/cube.obj");

public:
    VBO vbo;
    VAO vao;

public:
    Cube();
    inline std::vector<Vertex2DTex> getObjectVertices() { return this->cube; };

    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, float side);
};
