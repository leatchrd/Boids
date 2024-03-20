#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "app.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

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
    App myApp;

    // Dear ImGui
    ctx.imgui = [&]() {
        myApp.drawMenu();
        myApp.pausePlayKey(ctx);
    };

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        // Event management
        myApp.exitKey(ctx);

        // Scene setup
        myApp.draw(ctx, 0.2);
        myApp.update(ctx);
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();
}
