#pragma once
#include "p6/p6.h"

class TrackballCamera {
private:
    float _distance; // distance to scene center
    float _angleX;   // camera rotation angle on X axes --> top / bottom
    float _angleY;   // camera rotation angle on Y axes --> left / right

public:
    TrackballCamera()
        : _distance{-5.f}, _angleX{0.f}, _angleY{0.f} {};

    inline void moveFront(float delta) { this->_distance += delta; };    // move forward / backward
    inline void rotateUp(float degrees) { this->_angleX += degrees; };   // rotate vertically
    inline void rotateLeft(float degrees) { this->_angleY += degrees; }; // rotate laterally

    const glm::mat4 getViewMatrix();
    void            updateTrackballCamera(p6::Context& ctx);
};
