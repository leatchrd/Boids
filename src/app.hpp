#pragma once

#include "p6/p6.h"
#include "scene.hpp"

class App {
private:
    Scene scene;

public:
    App();

    void drawMenu();
    void update(p6::Context& ctx);
    void draw(p6::Context& ctx);

    void pausePlayKey(p6::Context& ctx);
    void exitKey(p6::Context& ctx);
};
