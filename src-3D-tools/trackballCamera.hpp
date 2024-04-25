#pragma once
#include "p6/p6.h"

class TrackballCamera {
private:
    float distance; // distance to scene center
    float angleX;   // camera rotation angle on X axes --> top / bottom
    float angleY;   // camera rotation angle on Y axes --> left / right

public:
    TrackballCamera()
        : distance{-5.f}, angleX{0.f}, angleY{0.f} {};

    inline void moveFront(float delta) { this->distance += delta; };    // move forward / backward
    inline void rotateUp(float degrees) { this->angleX += degrees; };   // rotate vertically
    inline void rotateLeft(float degrees) { this->angleY += degrees; }; // rotate laterally

    const glm::mat4 getViewMatrix();
    void            updateOrientation(p6::Context& ctx);
};
