/****************************************************************************************

Game engine for ERTS 2024-2025 project, second version

This engine supports three different states:
- Main Menu
- Playing Game
- Exit Game

The engine is implemented using the State design pattern. 
The GameContext class is the context class that holds the current state. 
The three states are implemented as singletons.

*****************************************************************************************/
#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cmath>

using std::string;

template <typename T>
class Vec2 {
public:
    T x, y;
    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(T scalar) const {
        return Vec2(x * scalar, y * scalar);
    }
    
    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }

    Vec2<int> toInt() const {
        return Vec2<int>(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));
    }
};

class Rectangle2D {
public:
    Rectangle2D(Vec2<int> size, Vec2<int> position, uint32_t color) 
        : size(size), position(position), color(color) {}

    void draw() {
        std::cout << "Drawing rectangle at (" << position.x << ", " << position.y 
                  << ") with size (" << size.x << ", " << size.y 
                  << ") and color " << static_cast<int>(color) << "\n";
    }

    Vec2<int> size;
    Vec2<int> position;
    uint32_t color;
};

// forward declarations
class GameScene;
class GameContext;
class GameObject;
class GameObject {
public:
    Rectangle2D shape;
    Vec2<float> velocity;
    Vec2<float> acceleration;

    GameObject(Rectangle2D shape) : shape(shape), velocity({0.0f, 0.0f}), acceleration({0.0f, 0.0f}) {}

    virtual void update() = 0;
    virtual void render() {
        shape.draw();
    }
};

class GameScene {
public:
    void update() {
        for (auto gameObject : gameObjects) {
            gameObject->update();
        }
    }

    void render() {
        for (auto gameObject : gameObjects) {
            gameObject->render();
        }
    }

    std::vector<GameObject*> gameObjects; // Use raw pointers
};


// Game engine context class

class GameContext {

    public:
        void setScene(GameScene * scene){
            currentScene = scene;
        }
        void update(){
            currentScene->update();
        }
        void render(){
            currentScene->render();
        }

    private:
        GameScene * currentScene;
};

