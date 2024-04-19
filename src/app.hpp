#pragma once
#include "3DTools.hpp"
#include "flock.hpp"
#include "loader.h"
#include "p6/p6.h"
#include "scene.hpp"
#include "texture.hpp"

class App {
private:
    Scene  scene;
    Flock  flock;
    size_t totalBoids;

private:
    void pausePlayKey(p6::Context& ctx);
    void exitKey(p6::Context& ctx);

public:
    App(size_t nbBoids);

    void  drawMenu();
    void  checkEvents(p6::Context& ctx);
    float getAquariumDetailLevel() { return this->scene.getAquariumDetailLevel(); };

    void updateFlock(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, Texture& texLittleFish, Texture& texMediumFish, Texture& texBigFish, const std::vector<vertex>& fishVertexContainer);
    void drawScene(p6::Context& ctx, const glm::mat4 camMVMatrix, const GLint& uni_MVP, const GLint& uni_MV, const GLint& uni_Normal, const std::vector<Vertex2DTex>& cubeContainer);
};
