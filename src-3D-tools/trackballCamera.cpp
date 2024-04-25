#include "trackballCamera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "p6/p6.h"

const glm::mat4 TrackballCamera::getViewMatrix()
{
    // moving the camera is like moving the whole scene in the opposite direction
    glm::mat4 MVMatrix = glm::translate(glm::mat4{1.f}, glm::vec3{0.f, 0.f, this->distance});
    MVMatrix           = glm::rotate(MVMatrix, -this->angleX, glm::vec3{1.f, 0.f, 0.f});
    MVMatrix           = glm::rotate(MVMatrix, -this->angleY, glm::vec3{0.f, 1.f, 0.f});
    return MVMatrix;
};

void TrackballCamera::updateOrientation(p6::Context& ctx)
{
    // mouse_dragged events also available
    if (ctx.key_is_pressed(GLFW_KEY_UP)) // rotate up
    {
        this->rotateUp(ctx.delta_time());
    }
    else if (ctx.key_is_pressed(GLFW_KEY_DOWN)) // rotate down
    {
        this->rotateUp(-ctx.delta_time());
    }
    if (ctx.key_is_pressed(GLFW_KEY_LEFT)) // rotate left
    {
        this->rotateLeft(ctx.delta_time());
    }
    else if (ctx.key_is_pressed(GLFW_KEY_RIGHT)) // rotate right
    {
        this->rotateLeft(-ctx.delta_time());
    }
}
