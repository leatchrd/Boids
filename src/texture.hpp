#pragma once
#include "p6/p6.h"

class Texture {
private:
    const img::Image _image;
    GLuint           _id;

public:
    Texture(std::string imagePath, GLuint id);

    inline void bind()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->_id);
    };
    inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };

    void loadTexImageAndParam();
};
