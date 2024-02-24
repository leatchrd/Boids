#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "boid.hpp"
#include "doctest/doctest.h"
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
    Scene     myScene(glm::vec2{0.f, 0.f}, 0.8);
    Boid      boid1(glm::vec2{0.f, 0.f}, glm::vec2{0.002, 0.002}, glm::vec2{0.0, 0.0});
    glm::vec2 click_force{0.0001, 0.0001};

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        if (ctx.mouse_button_is_pressed(p6::Button::Left))
        {
            boid1.addForce(click_force);
        }

        // Scene setup
        myScene.draw(ctx, 0.2);

        // Draws one small circle in the center
        boid1.draw(ctx);
        boid1.update();
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();
}
