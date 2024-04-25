#pragma once
#include "loader.h"
#include "p6/p6.h"
#include "texture.hpp"
#include "vao.hpp"
#include "vbo.hpp"

class Seaweed {
private:
    const Object3D seaweed = loadOBJ("assets/models/seaweed.obj");

public:
    VBO vbo;
    VAO vao;

public:
    Seaweed();
    void update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, Texture& texSeaweed1, Texture& texSeaweed2);
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, glm::vec3 position, float angle, float scale);
};
