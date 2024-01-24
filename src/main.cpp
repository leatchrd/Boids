#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "p6/p6.h"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Awesome-Boids-Project"}};

    // LT Dessiner un carré
    auto square_radius = 0.7f;

    ctx.maximize_window();

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        // LT Dessiner un carré
        ctx.square(
            p6::Center{},
            p6::Radius{square_radius}
        );

        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}