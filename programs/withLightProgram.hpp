#pragma once
#include "p6/p6.h"

class WithLightProgram {
public:
    p6::Shader program;

    GLint uniMVP;
    GLint uniMV;
    GLint uniNormal;

    GLint uniTexture;
    GLint uniDetailLevel;

    GLint uniKd;
    GLint uniKs;
    GLint uniShininess;

    GLint uniLightDirection;
    GLint uniLightIntensity;

    WithLightProgram()
        : program{p6::load_shader("shaders/3D.vs.glsl", "shaders/pointLight.fs.glsl")}
    {
        uniMVP            = glGetUniformLocation(this->program.id(), "uMVPMatrix");
        uniMV             = glGetUniformLocation(this->program.id(), "uMVMatrix");
        uniNormal         = glGetUniformLocation(this->program.id(), "uNormalMatrix");
        uniTexture        = glGetUniformLocation(this->program.id(), "uTexture");
        uniDetailLevel    = glGetUniformLocation(this->program.id(), "uDetailLevel");
        uniKd             = glGetUniformLocation(this->program.id(), "uKd");
        uniKs             = glGetUniformLocation(this->program.id(), "uKs");
        uniShininess      = glGetUniformLocation(this->program.id(), "uShininess");
        uniLightDirection = glGetUniformLocation(this->program.id(), "uLightDir_vs");
        uniLightIntensity = glGetUniformLocation(this->program.id(), "uLightIntensity");
    }
};
