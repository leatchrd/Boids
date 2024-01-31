#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
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
    auto square_radius = 0.7f;

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        // Draws a square in the center
        ctx.square(
            p6::Center{},
            p6::Radius{square_radius}
        );

        // Draws one small triangle in the center
        ctx.triangle(
            p6::Point2D{0.f, 0.f},
            p6::Point2D(0.1, 0.f),
            p6::Point2D(0.f, 0.1),
            p6::Center{},
            p6::Rotation{}
        );

        // Draws a circle that follows the mouse
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
    };

    // STARTS THE INFINITE LOOP
    ctx.start();
}