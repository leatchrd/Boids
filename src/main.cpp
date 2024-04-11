#include <cstdlib>
#include "trackballCamera.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "3DTools.hpp"
#include "app.hpp"
#include "appPrograms.hpp"
#include "doctest/doctest.h"
#include "glimac/common.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "loader.h"
#include "p6/p6.h"
#include "texture.hpp"
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
    App         myApp;
    BoidProgram myBoidProgram;
    CubeProgram myCubeProgram;

    TrackballCamera mainCamera;

    // TEXTURES
    Textures allTextures(3);
    allTextures.gen();

    Texture texWater("assets/textures/water.jpg", allTextures._textures[0]);
    texWater.bind();
    texWater.loadTexImageAndParam();
    texWater.unbind();

    Texture texGlass("assets/textures/glass_blue.png", allTextures._textures[1]);
    texGlass.bind();
    texGlass.loadTexImageAndParam();
    texGlass.unbind();

    Texture texFishScalesColor("assets/textures/fish_scales_mult_color.png", allTextures._textures[2]);
    texFishScalesColor.bind();
    texFishScalesColor.loadTexImageAndParam();
    texFishScalesColor.unbind();

    // SINGLE WALL
    // object creation
    const Object3D cube = loadOBJ("assets/models/cube_1.obj");

    // VBO creation & binding
    VBO vboWall(1);
    vboWall.gen();
    vboWall.bind();

    glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(vertex), cube.vertices.data(), GL_STATIC_DRAW);
    vboWall.unbind();

    // VAO creation & binding
    VAO vaoWall(1);
    vaoWall.gen();
    vaoWall.bind();
    vaoWall.activateAttributes();

    // VBO re-binding
    vboWall.bind();

    vaoWall.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    // VBO de-binding & VAO de-binding
    vboWall.unbind();
    vaoWall.unbind();

    // SINGLE FISH
    // VBO creation & binding
    VBO vboFish(2);
    vboFish.gen();
    vboFish.bind();

    // vertices creation
    const std::vector<glimac::ShapeVertex> fish = glimac::sphere_vertices(1.f, 32, 16);
    glBufferData(GL_ARRAY_BUFFER, fish.size() * sizeof(glimac::ShapeVertex), fish.data(), GL_STATIC_DRAW);

    vboFish.unbind();

    // VAO creation & binding
    VAO vaoFish(2);
    vaoFish.gen();
    vaoFish.bind();
    vaoFish.activateAttributes();

    // VBO re-binding
    vboFish.bind();

    vaoFish.setAttribPointer(sizeof(glimac::ShapeVertex), (const GLvoid*)(offsetof(glimac::ShapeVertex, position)), (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords)));

    // VBO de-binding & VAO de-binding
    vboFish.unbind();
    vaoFish.unbind();

    // Activation depth test
    glEnable(GL_DEPTH_TEST);

    // Dear ImGui
    ctx.imgui = [&]() {
        myApp.drawMenu();
        myApp.pausePlayKey(ctx);
    };

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        // Event management
        myApp.exitKey(ctx);
        mainCamera.updateTrackballCamera(ctx);

        // clean window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // WALL
        // use shader
        myCubeProgram._program.use();
        glUniform1i(myCubeProgram.uniGlassTex, 0);

        // VAO and texture re-binding
        vaoWall.bind();
        texGlass.bind();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        myApp.drawScene(ctx, mainCamera.getViewMatrix(), myCubeProgram.uniMVP, myCubeProgram.uniMV, myCubeProgram.uniNormal, cube.vertices);

        glDisable(GL_BLEND);

        // VAO and texture de-binding
        texGlass.unbind();
        vaoWall.unbind();

        // FISH
        // use shader
        myBoidProgram._program.use();
        glUniform1i(myBoidProgram.uniFishTex, 0);

        // VAO and texture re-binding
        vaoFish.bind();
        texFishScalesColor.bind();

        myApp.updateFlock(ctx, mainCamera.getViewMatrix(), myBoidProgram.uniMVP, myBoidProgram.uniMV, myBoidProgram.uniNormal, fish);

        // VAO and texture de-binding
        texFishScalesColor.unbind();
        vaoFish.unbind();
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();

    // free memory --> automatic with VBO, VAO and Textures destructors
}
