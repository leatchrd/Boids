#include "trackballCamera.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "3DTools.hpp"
#include "app.hpp"
#include "appPrograms.hpp"
#include "doctest/doctest.h"
#include "glimac/common.hpp"
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
    App         myApp(20);
    BoidProgram myBoidProgram;
    CubeProgram myCubeProgram;

    TrackballCamera mainCamera;

    // TEXTURES
    Textures allTextures(5);
    allTextures.gen();

    Texture texFish1("assets/textures/goldfish_1.png", allTextures._textures[0]);
    Texture texFish2("assets/textures/goldfish_2.png", allTextures._textures[1]);
    Texture texFish3("assets/textures/goldfish_3.png", allTextures._textures[2]);
    Texture texWater("assets/textures/water.jpg", allTextures._textures[3]);
    Texture texGlass("assets/textures/glass_blue.png", allTextures._textures[4]);

    std::cout << "finish textures creation" << std::endl;

    // CUBE AQUARIUM
    // object creation
    // const Object3D cube = loadOBJ("assets/models/cube.obj");
    const std::vector<Vertex2DTex> cube = createCubeVertices();

    // VBO creation & binding
    VBO vboCube(1);
    vboCube.gen();
    vboCube.bind();

    glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(Vertex2DTex), cube.data(), GL_STATIC_DRAW);
    vboCube.unbind();

    // VAO creation & binding
    VAO vaoCube(1);
    vaoCube.gen();
    vaoCube.bind();
    vaoCube.activateAttributes();

    // VBO re-binding
    vboCube.bind();

    vaoCube.setAttribPointer(sizeof(Vertex2DTex), (const GLvoid*)(offsetof(Vertex2DTex, position)), (const GLvoid*)(offsetof(Vertex2DTex, texture)));

    // VBO de-binding & VAO de-binding
    vboCube.unbind();
    vaoCube.unbind();

    // FISH
    // object creation
    const Object3D fish = loadOBJ("assets/models/goldfish.obj");

    // VBO creation & binding
    VBO vboFish(2);
    vboFish.gen();
    vboFish.bind();

    glBufferData(GL_ARRAY_BUFFER, fish.vertices.size() * sizeof(vertex), fish.vertices.data(), GL_STATIC_DRAW);
    vboFish.unbind();

    // VAO creation & binding
    VAO vaoFish(2);
    vaoFish.gen();
    vaoFish.bind();
    vaoFish.activateAttributes();

    // VBO re-binding
    vboFish.bind();

    vaoFish.setAttribPointer(sizeof(vertex), (const GLvoid*)(offsetof(vertex, position)), (const GLvoid*)(offsetof(vertex, uv)));

    // VBO de-binding & VAO de-binding
    vboFish.unbind();
    vaoFish.unbind();

    // Activation depth test
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Dear ImGui
    ctx.imgui = [&]() {
        myApp.drawMenu();
    };

    // INFINITE UPDATE LOOP
    ctx.update = [&]() {
        // Event management
        myApp.checkEvents(ctx);
        mainCamera.updateTrackballCamera(ctx);

        // clean window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // WALL
        // use shader
        myCubeProgram._program.use();
        glUniform1i(myCubeProgram.uniGlassTex, 0);

        // VAO and texture re-binding
        vaoCube.bind();
        texGlass.bind();

        glEnable(GL_BLEND);

        // myApp.drawScene(ctx, mainCamera.getViewMatrix(), myCubeProgram.uniMVP, myCubeProgram.uniMV, myCubeProgram.uniNormal, cube);

        glDisable(GL_BLEND);

        // VAO and texture de-binding
        texGlass.unbind();
        vaoCube.unbind();

        // FISH
        // use shader
        myBoidProgram._program.use();
        glUniform1i(myBoidProgram.uniFishTex, 0);

        // VAO and texture re-binding
        vaoFish.bind();
        texFish1.bind();

        myApp.updateFlock(ctx, mainCamera.getViewMatrix(), myBoidProgram.uniMVP, myBoidProgram.uniMV, myBoidProgram.uniNormal, fish.vertices);

        // VAO and texture de-binding
        texFish1.unbind();
        vaoFish.unbind();
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();

    // free memory --> automatic with VBO, VAO and Textures destructors
}
