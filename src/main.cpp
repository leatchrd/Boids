#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "boid.hpp"
#include "doctest/doctest.h"
#include "flock.hpp"
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
    // Flock     myFlock(5);
    glm::vec2 click_force{0.000001, 0.000001};

    // Dear ImGui
    ctx.imgui = [&]() {
        display.createMenu(myScene);
    };

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        // Event management
        myScene.dealWithFKeyPressed(ctx, click_force);
        myScene.dealWithWallCollisions();

        // Scene setup
        myScene.draw(ctx, 0.2);
        myScene.update(ctx);
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();
}
