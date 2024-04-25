#pragma once
#include "loader.h"
#include "p6/p6.h"
#include "vao.hpp"
#include "vbo.hpp"

class Submarine {
private:
    const Object3D submarine = loadOBJ("assets/models/submarine.obj");

    glm::vec3 position;
    float     radius;

public:
    VBO vbo;
    VAO vao;

private:
    void moveFront(float delta, float wall);
    void moveLeft(float delta, float wall);
    void moveUp(float delta, float wall);

    void updatePosition(p6::Context& ctx, float wall);
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal);

public:
    Submarine();
    void update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, float wall);
};
