#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "boid.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // INITIALIZATION
    // Creates the application's window
    auto ctx = p6::Context{{.title = "Awesome-Boids-Project"}};
    ctx.maximize_window();

    // Square parameters
    auto square_radius = 0.8f;

    // Circle parameters
    Boid boid1(glm::vec2{0.f, 0.f}, glm::vec2{0.002, 0.004});

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        // Draws a square in the center
        ctx.square(
            p6::Center{},
            p6::Radius{square_radius}
        );

        // Draws one small circle in the center
        boid1.draw(ctx);
        boid1.update();

        // Draws a circle that follows the mouse
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
    };

    // STARTS THE INFINITE LOOP
    ctx.start();
}
