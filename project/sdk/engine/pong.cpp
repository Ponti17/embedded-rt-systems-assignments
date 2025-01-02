#include "pong.h"

static bool upSignal1;
static bool downSignal1;
static bool upSignal2;
static bool downSignal2;

static PongTheGame* PingPong;

void initializeGame() {

    // Set up game objects

    auto PingPong = new PongTheGame();
    auto paddle1 = new Paddle({10, 50}, {0, 0}, 255);
    auto paddle2 = new Paddle({10, 50}, {100, 0}, 255);
    auto ball = new Ball({5, 5}, {50, 50}, 255, {1, 1});

    auto scene = new GameScene();
    scene->gameObjects.push_back(std::unique_ptr<GameObject>(paddle1));
    scene->gameObjects.push_back(std::unique_ptr<GameObject>(paddle2));
    scene->gameObjects.push_back(std::unique_ptr<GameObject>(ball));

    PingPong->setScene(scene);

    // Set up input signals
    paddle1->upSignal = &upSignal1;
    paddle1->downSignal = &downSignal1;
    paddle2->upSignal = &upSignal2;
    paddle2->downSignal = &downSignal2;

}

void updateGame() {

    PingPong->update();

    PingPong->render();
    
}