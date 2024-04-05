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
    App myApp;

    // Load shader
    const p6::Shader shader =
        p6::load_shader("shaders/3D.vs.glsl", "shaders/tex3D.fs.glsl");

    // TEXTURES
    GLsizei             nb_textures = 2;
    std::vector<GLuint> textures{0};
    glGenTextures(nb_textures, textures.data());

    const img::Image water         = p6::load_image_buffer("assets/textures/water.jpg");
    GLuint           waterTexIndex = textures[0];
    glBindTexture(GL_TEXTURE_2D, waterTexIndex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, water.width(), water.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, water.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    const img::Image glass         = p6::load_image_buffer("assets/textures/glass_blue.png");
    GLuint           glassTexIndex = textures[1];
    glBindTexture(GL_TEXTURE_2D, glassTexIndex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glass.width(), glass.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glass.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    const img::Image fishScalesColor   = p6::load_image_buffer("assets/textures/fish_scales_mult_color.png", false);
    GLuint           fishColorTexIndex = textures[2];
    glBindTexture(GL_TEXTURE_2D, fishColorTexIndex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fishScalesColor.width(), fishScalesColor.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, fishScalesColor.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

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
    GLuint vaoWall;
    glGenVertexArrays(1, &vaoWall);
    glBindVertexArray(vaoWall);

    // vertex attribute activation
    static constexpr GLuint wall_position = 0;
    glEnableVertexAttribArray(wall_position);
    static constexpr GLuint wall_norm = 1;
    glEnableVertexAttribArray(wall_norm);
    static constexpr GLuint wall_tex_coords = 2;
    glEnableVertexAttribArray(wall_tex_coords);

    // VBO re-binding
    vboWall.bind();

    glVertexAttribPointer(
        wall_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DTex),
        (const GLvoid*)(offsetof(Vertex2DTex, position))
    );
    glVertexAttribPointer(
        wall_norm, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DTex),
        (const GLvoid*)(offsetof(Vertex2DTex, norm))
    );
    glVertexAttribPointer(
        wall_tex_coords, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DTex),
        (const GLvoid*)(offsetof(Vertex2DTex, texture))
    );

    // VBO de-binding & VAO de-binding
    vboWall.unbind();
    glBindVertexArray(0);

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
    GLuint vaoFish;
    glGenVertexArrays(1, &vaoFish);
    glBindVertexArray(vaoFish);

    // vertex attribute activation
    static constexpr GLuint fish_position = 0;
    glEnableVertexAttribArray(fish_position);
    static constexpr GLuint fish_norm = 1;
    glEnableVertexAttribArray(fish_norm);
    static constexpr GLuint fish_tex_coords = 2;
    glEnableVertexAttribArray(fish_tex_coords);

    // VBO re-binding
    vboFish.bind();

    glVertexAttribPointer(
        fish_position, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
        (const GLvoid*)(offsetof(glimac::ShapeVertex, position))
    );
    glVertexAttribPointer(
        fish_norm, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
        (const GLvoid*)(offsetof(glimac::ShapeVertex, normal))
    );
    glVertexAttribPointer(
        fish_tex_coords, 2, GL_FLOAT, GL_FALSE,
        sizeof(glimac::ShapeVertex),
        (const GLvoid*)(offsetof(glimac::ShapeVertex, texCoords))
    );

    // VBO de-binding & VAO de-binding
    vboFish.unbind();
    glBindVertexArray(0);

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
        glBindVertexArray(vaoWall);
        glBindTexture(GL_TEXTURE_2D, glassTexIndex);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        myApp.drawScene(ctx, uni_MVP, uni_MV, uni_Normal, wall);

        glDisable(GL_BLEND);

        // VAO and texture de-binding
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

        // FISH
        // VAO and texture re-binding
        glBindVertexArray(vaoFish);
        glBindTexture(GL_TEXTURE_2D, fishColorTexIndex);

        myApp.updateFlock(ctx, uni_MVP, uni_MV, uni_Normal, fish);

        // VAO and texture de-binding
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    };

    // EVENTS & QUERIES

    // STARTS THE INFINITE LOOP
    ctx.start();

    // free memory
    glDeleteTextures(nb_textures, textures.data());
    // automatic with VBO destructor

    glDeleteVertexArrays(1, &vaoWall);

    glDeleteVertexArrays(1, &vaoFish);
}
