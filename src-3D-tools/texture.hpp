#pragma once
#include "p6/p6.h"

class Texture {
private:
    const img::Image _image;
    GLuint           _id;
    GLenum           _nb;

public:
    Texture(std::string imagePath, GLuint id, GLenum nb)
        : _image{p6::load_image_buffer(imagePath)}, _id{id}, _nb{nb}
    {
        this->bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_image.width(), this->_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_image.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        this->unbind();
    };

    inline void bind() { glBindTexture(GL_TEXTURE_2D, this->_id); };
    inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
    inline void activate() { glActiveTexture(this->_nb); };
};
