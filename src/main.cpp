#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "3DTools.hpp"
#include "app.hpp"
#include "doctest/doctest.h"
#include "glimac/common.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
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

    // Load shader
    const p6::Shader shader =
        p6::load_shader("shaders/3D.vs.glsl", "shaders/tex3D.fs.glsl");

    // Different parameters
    App myApp;

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
    // VBO creation & binding
    VBO vboWall(1);
    vboWall.gen();
    vboWall.bind();

    // vertices creation
    std::vector<Vertex2DTex> wall;
    wall.push_back(Vertex2DTex{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    wall.push_back(Vertex2DTex{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.f, 1.f}});
    wall.push_back(Vertex2DTex{{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});
    wall.push_back(Vertex2DTex{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.f, 1.f}});
    wall.push_back(Vertex2DTex{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.f, 0.f}});
    wall.push_back(Vertex2DTex{{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.f, 0.f}});

    glBufferData(GL_ARRAY_BUFFER, wall.size() * sizeof(Vertex2DTex), wall.data(), GL_STATIC_DRAW);
    vboWall.unbind();

    // VAO creation & binding
    VAO vaoWall(1);
    vaoWall.gen();
    vaoWall.bind();
    vaoWall.activateAttributes();

    // VBO re-binding
    vboWall.bind();

    vaoWall.setAttribPointer(sizeof(Vertex2DTex), (const GLvoid*)(offsetof(Vertex2DTex, position)), (const GLvoid*)(offsetof(Vertex2DTex, texture)));

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

    // Uniform variable info
    GLint uni_MVP    = glGetUniformLocation(shader.id(), "uMVPMatrix");
    GLint uni_MV     = glGetUniformLocation(shader.id(), "uMVMatrix");
    GLint uni_Normal = glGetUniformLocation(shader.id(), "uNormalMatrix");
    GLint uni_tex    = glGetUniformLocation(shader.id(), "uTexture");

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

        // clean window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // use given shader
        shader.use();
        glUniform1i(uni_tex, 0);

        // WALL
        // VAO and texture re-binding
        vaoWall.bind();
        texGlass.bind();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        myApp.drawScene(ctx, uni_MVP, uni_MV, uni_Normal, wall);

        glDisable(GL_BLEND);

        // VAO and texture de-binding
        texGlass.unbind();
        vaoWall.unbind();

        // FISH
        // VAO and texture re-binding
        vaoFish.bind();
        texFishScalesColor.bind();

        myApp.updateFlock(ctx, uni_MVP, uni_MV, uni_Normal, fish);

        // VAO and texture de-binding
        texFishScalesColor.unbind();
        vaoFish.unbind();
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();

    // free memory --> automatic with VBO, VAO and Textures destructors
}
