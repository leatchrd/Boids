#pragma once

#include "p6/p6.h"

class Vertex2DTex {
public:
    glm::vec3 position, norm;
    glm::vec2 texture;

    Vertex2DTex(glm::vec3 position, glm::vec3 norm, glm::vec2 texture)
        : position(position), norm(norm), texture(texture){};
};
