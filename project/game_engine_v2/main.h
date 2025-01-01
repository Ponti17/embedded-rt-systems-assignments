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

struct inputSignal {
    bool* signal;
    string name;
    inputSignal(bool* signal, string name) : signal(signal), name(name) {};
};

// forward declarations
class MainMenu;
class PlayingGame;
class ExitGame;
class GameContext;
class GameObject;

class GameScene{
    public: 

        virtual ~GameScene() = default;
        virtual void handleInput() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        GameScene(const GameScene&) = delete;
        GameScene& operator=(const GameScene&) = delete;

        //events that can change state
        virtual void onStart(GameContext * gameContext) {};
        virtual void onExit(GameContext * gameContext) {};
        virtual void onGameOver(GameContext * gameContext) {};

        //All scenes holds a list of objects that must be implemented by the game
        std::vector<GameObject> gameObjects;

    protected:
        GameScene() = default;
};


//implementation of the three scenes / game states
// All must be implemented as singletons
class MainMenu : public GameScene {

    public:
        static MainMenu& getInstance() {
            static MainMenu instance;
            return instance;
        }

        void handleInput() override {
            std::cout << "Main Menu: handleInput" << std::endl;
        }

        void update() override {
            std::cout << "Main Menu: update" << std::endl;
        }

        void render() override {
            std::cout << "Main Menu: render" << std::endl;
        }

        MainMenu() = default;
        ~MainMenu() = default;

};

class PlayingGame : public GameScene {

    public:
        static PlayingGame& getInstance() {
            static PlayingGame instance;
            return instance;
        }

        void handleInput() override {
            std::cout << "Playing Game: handleInput" << std::endl;
        }

        void update() override {
            std::cout << "Playing Game: update" << std::endl;
        }

        void render() override {
            std::cout << "Playing Game: render" << std::endl;
        }

        PlayingGame() = default;
        ~PlayingGame() = default;

};

class ExitGame : public GameScene {

    public:
        static ExitGame& getInstance() {
            static ExitGame instance;
            return instance;
        }

        void handleInput() override {
            std::cout << "Exit Game: handleInput" << std::endl;
        }

        void update() override {
            std::cout << "Exit Game: update" << std::endl;
        }

        void render() override {
            std::cout << "Exit Game: render" << std::endl;
        }

        ExitGame() = default;
        ~ExitGame() = default;

};

// Game engine context class

class GameContext {

    public:
        GameContext() : currentScene(nullptr), isRunning(false) {}; 
        ~GameContext();
        
        void setScene(GameScene * scene){
            currentScene = scene;
        };

        void handleInput(){
            currentScene->handleInput();
        };
        void update(){
            currentScene->update();
        };
        void render(){
            currentScene->render();
        };

    private:
        GameScene * currentScene;
        bool isRunning;
        std::vector<inputSignal> inputSignals;
};

class GameObject {
    public:


}