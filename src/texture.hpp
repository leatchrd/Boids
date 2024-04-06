#pragma once
#include "p6/p6.h"

class Texture {
private:
    const img::Image _image;
    GLuint           _id;

public:
    Texture(std::string imagePath, GLuint id)
        : _image{p6::load_image_buffer(imagePath)}, _id{id} {};

    inline void bind()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->_id);
    };
    inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };

    void loadTexImageAndParam();
};

class Textures {
public:
    GLuint              _nbTextures;
    std::vector<GLuint> _textures{0};

public:
    Textures(GLuint nbTextures)
        : _nbTextures{nbTextures} {};
    ~Textures() { glDeleteTextures(this->_nbTextures, this->_textures.data()); };

    inline void gen() { glGenTextures(this->_nbTextures, this->_textures.data()); };
};
