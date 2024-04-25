#pragma once
#include "p6/p6.h"

class Textures {
public:
    GLuint              nbTextures = 10;                        // possible "seg fault" ONLY ON MAC if
    std::vector<GLuint> textures{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // these values aren't hard coded

public:
    Textures() { glGenTextures(this->nbTextures, this->textures.data()); };
    ~Textures() { glDeleteTextures(this->nbTextures, this->textures.data()); };
};
