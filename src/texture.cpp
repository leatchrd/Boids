#include "texture.hpp"
#include "p6/p6.h"

void Texture::loadTexImageAndParam()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_image.width(), this->_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
