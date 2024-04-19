#pragma once
#include "p6/p6.h"

class CubeProgram {
public:
    p6::Shader _program;
    GLint      uniMVP;
    GLint      uniMV;
    GLint      uniNormal;
    GLint      uniGlassTex;
    GLint      uniDetailLevel;

    CubeProgram()
        : _program{p6::load_shader("shaders/3D.vs.glsl", "shaders/cubeTex3D.fs.glsl")}
    {
        uniMVP         = glGetUniformLocation(this->_program.id(), "uMVPMatrix");
        uniMV          = glGetUniformLocation(this->_program.id(), "uMVMatrix");
        uniNormal      = glGetUniformLocation(this->_program.id(), "uNormalMatrix");
        uniGlassTex    = glGetUniformLocation(this->_program.id(), "uTextureGlass");
        uniDetailLevel = glGetUniformLocation(this->_program.id(), "uDetailLevel");
    }
};

class BoidProgram {
public:
    p6::Shader _program;
    GLint      uniMVP;
    GLint      uniMV;
    GLint      uniNormal;
    GLint      uniFishTex;

    BoidProgram()
        : _program{p6::load_shader("shaders/3D.vs.glsl", "shaders/fishTex3D.fs.glsl")}
    {
        uniMVP     = glGetUniformLocation(this->_program.id(), "uMVPMatrix");
        uniMV      = glGetUniformLocation(this->_program.id(), "uMVMatrix");
        uniNormal  = glGetUniformLocation(this->_program.id(), "uNormalMatrix");
        uniFishTex = glGetUniformLocation(this->_program.id(), "uTextureFish");
    }
};
