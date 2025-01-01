#pragma once

#include "game_engine.h"

// Shapes 
class PaddleShape : public Shape2D {

    Vec2 <int> size = {10, 50};
    void draw() override {
        std::cout << "Drawing Paddle" << std::endl;
    }

};

class BallShape : public Shape2D {

    Vec2 <int> size = {5, 5};
    void draw() override {
        std::cout << "Drawing Ball" << std::endl;
    }

};

// Game Objects
class Paddle : public GameObject {
public:
    Paddle () {
        shape = new PaddleShape();
    }

};

class Ball : public GameObject {
public:
    Ball () {
        shape = new BallShape();
    }

};

