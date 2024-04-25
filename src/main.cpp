#include "trackballCamera.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "app.hpp"
#include "doctest/doctest.h"
#include "p6/p6.h"
#include "texture.hpp"
#include "textures.hpp"
#include "withLightProgram.hpp"

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
    App              myApp(20);
    WithLightProgram myProgram;
    TrackballCamera  mainCamera;

    // TEXTURES
    Textures allTextures;
    Texture  texFish1("assets/textures/goldfish_1.png", allTextures.textures[0], GL_TEXTURE0);
    Texture  texFish2("assets/textures/goldfish_2.png", allTextures.textures[1], GL_TEXTURE0);
    Texture  texFish3("assets/textures/goldfish_3.png", allTextures.textures[2], GL_TEXTURE0);
    Texture  texSub("assets/textures/yellow_concrete.jpg", allTextures.textures[3], GL_TEXTURE1);
    Texture  texCoral1("assets/textures/coral_1.png", allTextures.textures[4], GL_TEXTURE2);
    Texture  texCoral2("assets/textures/coral_2.png", allTextures.textures[5], GL_TEXTURE2);
    Texture  texCoral3("assets/textures/coral_3.png", allTextures.textures[6], GL_TEXTURE2);
    Texture  texSeaweed1("assets/textures/seaweed_1.png", allTextures.textures[7], GL_TEXTURE3);
    Texture  texSeaweed2("assets/textures/seaweed_2.png", allTextures.textures[8], GL_TEXTURE3);
    Texture  texWater("assets/textures/water_a25.png", allTextures.textures[9], GL_TEXTURE4);

    // Global configuration
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Dear ImGui
    ctx.imgui = [&]() {
        myApp.drawMenu();
        myApp.checkWindowQueries(ctx);
    };

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        // Event management
        mainCamera.updateOrientation(ctx); // mouse_dragged events also available

        // clean window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Light direction
        glm::vec4 lightDir{1.0f, 1.0f, 1.0f, 1.0f};
        glm::vec4 newLightDir = lightDir * mainCamera.getViewMatrix();

        // AQUARIUM
        myProgram.program.use();
        glUniform1i(myProgram.uniTexture, 0);
        glUniform1f(myProgram.uniDetailLevel, myApp.getAquariumDetailLevel());
        glUniform3f(myProgram.uniKd, 1.0f, 1.0f, 1.0f);
        glUniform3f(myProgram.uniKs, 1.0f, 1.0f, 1.0f);
        glUniform1f(myProgram.uniShininess, 0.1f);
        glUniform3f(myProgram.uniLightDirection, newLightDir[0], newLightDir[1], newLightDir[2]);
        glUniform3f(myProgram.uniLightIntensity, 8.0f, 8.0f, 8.0f);

        // DRAW
        myApp.draw(ctx, mainCamera.getViewMatrix(), myProgram.uniMVP, myProgram.uniMV, myProgram.uniNormal, texFish1, texFish2, texFish3, texSub, texCoral1, texCoral2, texCoral3, texSeaweed1, texSeaweed2, texWater);
    };

    // EVENTS: camera orientation
    // scroll to zoom in/out on scene
    ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
        if (scroll.dy > 0)
        {
            mainCamera.moveFront(ctx.delta_time() * 3);
        }
        else if (scroll.dy < 0)
        {
            mainCamera.moveFront(-ctx.delta_time() * 3);
        }
    };
    // right click and drag to rotate left/right & up/down
    ctx.mouse_dragged = [&](p6::MouseDrag drag) {
        // keyboard queries also available
        if (ctx.mouse_button_is_pressed(p6::Button::Right))
        {
            mainCamera.rotateLeft(-drag.delta[0]);
            mainCamera.rotateUp(drag.delta[1]);
        }
    };

    // STARTS THE INFINITE LOOP
    ctx.start();
}
