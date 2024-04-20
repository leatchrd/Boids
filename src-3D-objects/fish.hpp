#pragma once
#include "loader.h"
#include "vao.hpp"
#include "vbo.hpp"

class Fish {
private:
    const Object3D fish = loadOBJ("assets/models/goldfish.obj");

public:
    VBO vbo;
    VAO vao;

public:
    Fish();
    inline std::vector<vertex> getObjectVertices() { return fish.vertices; };
};
