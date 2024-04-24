#include "trackballCamera.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "app.hpp"
#include "aquariumProgram.hpp"
#include "cube.hpp"
#include "doctest/doctest.h"
#include "fish.hpp"
#include "glimac/common.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "submarine.hpp"
#include "texture.hpp"
#include "textures.hpp"
#include "vao.hpp"
#include "vbo.hpp"

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
    App             myApp(20);
    Fish            fish;      // TODO: add to App
    Cube            cube;      // TODO: add to App
    Submarine       submarine; // TODO: add to App
    AquariumProgram myAquariumProgram;

    TrackballCamera mainCamera;

    // TEXTURES
    Textures allTextures;
    Texture  texFish1("assets/textures/goldfish_1.png", allTextures._textures[0], GL_TEXTURE0);
    Texture  texFish2("assets/textures/goldfish_2.png", allTextures._textures[1], GL_TEXTURE0);
    Texture  texFish3("assets/textures/goldfish_3.png", allTextures._textures[2], GL_TEXTURE0);
    Texture  texSub("assets/textures/yellow_concrete.jpg", allTextures._textures[3], GL_TEXTURE1);
    Texture  texWater("assets/textures/water_a25.png", allTextures._textures[4], GL_TEXTURE2);
    // Texture  texGlass("assets/textures/glass_blue.png", allTextures._textures[4], GL_TEXTURE1);

    // Global configuration
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Dear ImGui
    ctx.imgui = [&]() {
        myApp.drawMenu();
    };

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        // Event management
        myApp.checkWindowQueries(ctx);
        mainCamera.updateOrientation(ctx); // mouse_dragged events also available

        // clean window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // AQUARIUM
        myAquariumProgram.program.use();
        glUniform1i(myAquariumProgram.uniTexture, 0);
        glUniform1f(myAquariumProgram.uniDetailLevel, myApp.getAquariumDetailLevel());

        // FISH
        fish.vao.bind();
        myApp.updateFlock(ctx, mainCamera.getViewMatrix(), myAquariumProgram.uniMVP, myAquariumProgram.uniMV, myAquariumProgram.uniNormal, texFish1, texFish2, texFish3, fish.getObjectVertices());

        // SUBMARINE
        submarine.vao.bind();
        texSub.bind();
        submarine.update(ctx, mainCamera.getViewMatrix(), myAquariumProgram.uniMVP, myAquariumProgram.uniMV, myAquariumProgram.uniNormal, myApp.getWallSize());

        // CUBE
        cube.vao.bind();
        texWater.bind();
        myApp.drawScene(ctx, mainCamera.getViewMatrix(), myAquariumProgram.uniMVP, myAquariumProgram.uniMV, myAquariumProgram.uniNormal, cube.getObjectVertices());

        // unbinding
        texWater.unbind();
        cube.vao.unbind();

        texSub.unbind();
        submarine.vao.unbind();

        fish.vao.unbind();
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

    // free memory --> automatic with VBO, VAO and Textures destructors
}
