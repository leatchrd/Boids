#include <cstdlib>
#include "glm/fwd.hpp"
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

    // Circle parameters
    glm::vec2 direction{0.f, 0.f};

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        // Draws a square in the center
        ctx.square(
            p6::Center{},
            p6::Radius{square_radius}
        );

        // Draws one small circle in the center
        ctx.circle(
            p6::Center{direction},
            p6::Radius{0.03f}
        );
        direction += 0.005;

        // Draws a circle that follows the mouse
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
    };

    // STARTS THE INFINITE LOOP
    ctx.start();
}