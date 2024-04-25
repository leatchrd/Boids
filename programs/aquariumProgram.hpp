#pragma once
#include "p6/p6.h"

class AquariumProgram {
public:
    p6::Shader program;

    GLint uniMVP;
    GLint uniMV;
    GLint uniNormal;

    GLint uniTexture;
    GLint uniDetailLevel;

    AquariumProgram()
        : program{p6::load_shader("shaders/3D.vs.glsl", "shaders/aquariumTex3D.fs.glsl")}
    {
        uniMVP         = glGetUniformLocation(this->program.id(), "uMVPMatrix");
        uniMV          = glGetUniformLocation(this->program.id(), "uMVMatrix");
        uniNormal      = glGetUniformLocation(this->program.id(), "uNormalMatrix");
        uniTexture     = glGetUniformLocation(this->program.id(), "uTexture");
        uniDetailLevel = glGetUniformLocation(this->program.id(), "uDetailLevel");
    }
};
