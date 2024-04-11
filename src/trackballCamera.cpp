#include "trackballCamera.hpp"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_transform.hpp"
#include "p6/p6.h"

const glm::mat4 TrackballCamera::getViewMatrix()
{
    // moving the camera is like moving the whole scene in the opposite direction
    glm::mat4 MVMatrix = glm::translate(glm::mat4{1.f}, glm::vec3{0.f, 0.f, this->_distance});
    MVMatrix           = glm::rotate(MVMatrix, -this->_angleX, glm::vec3{1.f, 0.f, 0.f});
    MVMatrix           = glm::rotate(MVMatrix, -this->_angleY, glm::vec3{0.f, 1.f, 0.f});
    return MVMatrix;
};

void TrackballCamera::updateTrackballCamera(p6::Context& ctx)
{
    if (ctx.key_is_pressed(GLFW_KEY_UP))
    {
        this->moveFront(ctx.delta_time());
    }
    if (ctx.key_is_pressed(GLFW_KEY_DOWN))
    {
        this->moveFront(-ctx.delta_time());
    }
    if (ctx.key_is_pressed(GLFW_KEY_W))
    {
        this->rotateUp(ctx.delta_time());
    }
    if (ctx.key_is_pressed(GLFW_KEY_S))
    {
        this->rotateUp(-ctx.delta_time());
    }
    if (ctx.key_is_pressed(GLFW_KEY_A))
    {
        this->rotateLeft(ctx.delta_time());
    }
    if (ctx.key_is_pressed(GLFW_KEY_D))
    {
        this->rotateLeft(-ctx.delta_time());
    }
}
