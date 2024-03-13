#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "doctest/doctest.h"
#include "menu.hpp"
#include "p6/p6.h"
#include "scene.hpp"

int main(void)
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // INITIALIZATION
    // Creates the application's window
    auto ctx = p6::Context{{.title = "Awesome-Boids-Project"}};
    ctx.maximize_window();

    // Different parameters
    Menu  display;
    Scene myScene(glm::vec2{0.f, 0.f});

    // Dear ImGui
    ctx.imgui = [&]() {
        display.createMenu(myScene.side);
    };

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        myScene.draw(ctx, 0.2);
        myScene.update(ctx);
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();
}
