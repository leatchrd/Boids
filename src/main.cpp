#include <sys/_types/_size_t.h>
#include <cstdlib>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "boid.hpp"
#include "doctest/doctest.h"
#include "flock.hpp"
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
    Flock     myFlock(5);
    glm::vec2 click_force{0.001, 0.001};

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        if (ctx.key_is_pressed(GLFW_KEY_F))
        {
            myFlock.addForce(click_force);
        }

        for (size_t i = 0; i < myFlock.flock.size(); i++)
        {
            if (myScene.collisionWithWall(myFlock.flock[i]))
            {
                myFlock.flock[i].newDirectionWall();
            }
        }

        // Scene setup
        myScene.draw(ctx, 0.2);

        // Draws one small circle in the center
        myFlock.update(ctx);
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();
}
