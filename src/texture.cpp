#include "texture.hpp"
#include "p6/p6.h"

Texture::Texture(std::string imagePath, GLuint id)
    : _image{p6::load_image_buffer(imagePath, false)}, _id{id}
{
    this->bind();
    this->loadTexImageAndParam();
    this->unbind();
}

void Texture::loadTexImageAndParam()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_image.width(), this->_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
