#include "pong.h"

//Singletons definition
MainMenu * MainMenu::instance = nullptr;
PlayingGame * PlayingGame::instance = nullptr;
ExitGame * ExitGame::instance = nullptr;

int main(int argc, char** argv) {

    Paddle * player1, * player2;
    Ball* ball;

    PlayingGame::getInstance()->gameObjects.push_back(player1);
    PlayingGame::getInstance()->gameObjects.push_back(player2);
    PlayingGame::getInstance()->gameObjects.push_back(ball);
    
    auto PongTheGame = new GameContext();

    PongTheGame->gameLoop();

    return 0;
}