#pragma once
#include "p6/p6.h"

class Texture {
private:
    const img::Image _image;
    GLuint           _id;
    GLenum           _nb;

public:
    Texture(std::string imagePath, GLuint id, GLenum nb);

    inline void bind() { glBindTexture(GL_TEXTURE_2D, this->_id); };
    inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };

    inline void activate() { glActiveTexture(this->_nb); };

    void loadTexImageAndParam();
};
