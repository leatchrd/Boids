#pragma once
#include "loader.h"
#include "p6/p6.h"
#include "texture.hpp"
#include "vao.hpp"
#include "vbo.hpp"

class Coral {
private:
    const Object3D coral = loadOBJ("assets/models/coral.obj");

public:
    VBO vbo;
    VAO vao;

public:
    Coral();
    void update(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, Texture& texCoral1, Texture& texCoral2, Texture& texCoral3);
    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uniMVP, const GLint& uniMV, const GLint& uniNormal, glm::vec3 position, float angle, float scale);
};
