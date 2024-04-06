#pragma once

#include "3DTools.hpp"
#include "flock.hpp"
#include "loader.h"
#include "p6/p6.h"
#include "scene.hpp"

class App {
private:
    Scene scene;
    Flock flock;

public:
    App();

    void drawMenu();
    void updateFlock(p6::Context& ctx, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<glimac::ShapeVertex>& boidContainer);
    void drawScene(p6::Context& ctx, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<vertex>& cubeContainer);

    void pausePlayKey(p6::Context& ctx);
    void exitKey(p6::Context& ctx);
};
