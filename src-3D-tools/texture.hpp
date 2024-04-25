#pragma once
#include "p6/p6.h"

class Texture {
private:
    const img::Image image;
    GLuint           id;
    GLenum           nb;

public:
    Texture(std::string imagePath, GLuint id, GLenum nb)
        : image{p6::load_image_buffer(imagePath)}, id{id}, nb{nb}
    {
        this->bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->image.width(), this->image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->image.data());
        glGenerateMipmap(GL_TEXTURE_2D);
        this->unbind();
    };

    inline void bind() { glBindTexture(GL_TEXTURE_2D, this->id); };
    inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
    inline void activate() { glActiveTexture(this->nb); };
};
