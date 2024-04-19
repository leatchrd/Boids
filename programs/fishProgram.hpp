#pragma once
#include "p6/p6.h"

class FishProgram {
public:
    p6::Shader program;
    GLint      uniMVP;
    GLint      uniMV;
    GLint      uniNormal;
    GLint      uniFishTex;
    GLint      uniDetailLevel;

    FishProgram()
        : program{p6::load_shader("shaders/3D.vs.glsl", "shaders/fishTex3D.fs.glsl")}
    {
        uniMVP         = glGetUniformLocation(this->program.id(), "uMVPMatrix");
        uniMV          = glGetUniformLocation(this->program.id(), "uMVMatrix");
        uniNormal      = glGetUniformLocation(this->program.id(), "uNormalMatrix");
        uniFishTex     = glGetUniformLocation(this->program.id(), "uTextureFish");
        uniDetailLevel = glGetUniformLocation(this->program.id(), "uDetailLevel");
    }
};
