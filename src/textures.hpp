#pragma once
#include "p6/p6.h"

class Textures {
public:
    GLuint              _nbTextures = 10;                        // possible "seg fault" ONLY ON MAC if
    std::vector<GLuint> _textures{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // these values aren't hard coded

public:
    Textures() { glGenTextures(this->_nbTextures, this->_textures.data()); };
    ~Textures() { glDeleteTextures(this->_nbTextures, this->_textures.data()); };
};
