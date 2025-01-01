#include "pong.h"

//Singletons definition
MainMenu * MainMenu::instance = nullptr;
PlayingGame * PlayingGame::instance = nullptr;
ExitGame * ExitGame::instance = nullptr;

int main(int argc, char** argv) {

    Paddle *player1 = new Paddle();
    Paddle *player2 = new Paddle();
    Ball *ball = new Ball();

    player1->shape->position = {0, 0};
    player2->shape->position = {0, 0};

    ball->shape->position = {0, 0};

    ball->velocity = {0.0f, 0.0f};


    PlayingGame::getInstance()->gameObjects.push_back(player1);
    PlayingGame::getInstance()->gameObjects.push_back(player2);
    PlayingGame::getInstance()->gameObjects.push_back(ball);
    
    auto PongTheGame = std::make_unique<GameContext>();
    PongTheGame->gameLoop();

    return 0;
}