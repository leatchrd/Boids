#pragma once

#include "p6/p6.h"

enum idWallPosition {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    NOTHING
};

class Boid {
private:
    glm::vec2 position, velocity, acceleration, separation;
    float     radius;

    float perception_radius = 0.3;
    float maxSpeed          = 0.02;
    float maxAcceleration   = 0.0005;
    // float          separation_distance = 0.05;
    idWallPosition onWhichWall = NOTHING;

private:
    void updatePosition();
    void updateVelocity();
    void updateAcceleration(glm::vec2& force);

    void update();
    void flock(std::vector<Boid>& allBoids);

    bool inPerceptionRadius(Boid& boid);
    // bool inSeparationRadius(Boid& boid);

    // void separate(Boid& tooCloseBoid);
    glm::vec2 align(std::vector<Boid>& allBoids);

    void checkCollisionWithWall(float& wallSize);
    void setOnWhichWall(float& wallSize);
    void computeWallBounce();
    void computeNewDirectionAfterBounce(glm::vec2& norm);

public:
    Boid(float radius, glm::vec2 velocity);
    void run(std::vector<Boid>& allBoids, float& wallSize);

    void draw(p6::Context& ctx);
};
