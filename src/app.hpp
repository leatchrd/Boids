#pragma once
#include "coral.hpp"
#include "cube.hpp"
#include "fish.hpp"
#include "flock.hpp"
#include "p6/p6.h"
#include "scene.hpp"
#include "seaweed.hpp"
#include "submarine.hpp"
#include "texture.hpp"

class App {
private:
    Scene  scene;
    Flock  flock;
    size_t totalBoids;

    Fish      fishModel;
    Submarine submarineModel;
    Coral     coralModel;
    Seaweed   seaweedModel;
    Cube      cubeModel;

public:
    App(size_t nbBoids);

    void  drawMenu();
    void  checkWindowQueries(p6::Context& ctx);
    float getAquariumDetailLevel() { return this->scene.getAquariumDetailLevel(); };

    void draw(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, Texture& texLittleFish, Texture& texMediumFish, Texture& texBigFish, Texture& texSub, Texture& texCoral1, Texture& texCoral2, Texture& texCoral3, Texture& texSeaweed1, Texture& texSeaweed2, Texture& texCube);
};
