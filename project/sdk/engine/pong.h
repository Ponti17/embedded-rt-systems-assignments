#pragma once

#include "game_engine.h"

//Forward declarations
void initializeGame(void);
void updateGame(void);
// Shapes 
class Paddle2D : public Rectangle2D {};
class Ball2D : public Rectangle2D {};
// Game Objects
class Paddle : public GameObject {
public:

    bool* upSignal;
    bool* downSignal;

    int speed = 1;

    Paddle(Vec2<int> size, Vec2<int> position, uint32_t color) 
        : GameObject({size, position, color}) {}

    void update() override {
        if (upSignal) {
            shape.position.y -= 1 * speed;
        }
        if (downSignal) {
            shape.position.y += 1 * speed;
        }
    }
};

class Ball : public GameObject {
public:
    Vec2<float> velocity;
    float speed = 1;
    Ball(Vec2<int> size, Vec2<int> position, uint32_t color, Vec2<float> velocity)
        : GameObject({size, position, color}), velocity(velocity) {}

    void update() override {
        // Update position based on velocity

        velocity = velocity * speed;

        shape.position.x += static_cast<int>(velocity.x);
        shape.position.y += static_cast<int>(velocity.y);

        // Example collision logic
        if (shape.position.y <= 0 || shape.position.y >= 100) { // Boundary condition
            velocity.y = -velocity.y;
        }
    }
};

class PongTheGame : public GameContext{};