#pragma once
#include "loader.h"
#include "p6/p6.h"
#include "trackballCamera.hpp"
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

    // TrackballCamera camera;

private:
    void moveFront(float delta, float wall);
    void moveLeft(float delta, float wall);
    void moveUp(float delta, float wall);

    // void rotateUp(float degrees);
    // void rotateLeft(float degrees);

    void updatePosition(p6::Context& ctx, float wall);
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal);

public:
    Submarine();
    inline std::vector<vertex> getObjectVertices() { return this->submarine.vertices; };

    void update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, float wall);
};
