#include "pong.h"

//Singletons definition
MainMenu * MainMenu::instance = nullptr;
PlayingGame * PlayingGame::instance = nullptr;
ExitGame * ExitGame::instance = nullptr;

int main(int argc, char** argv) {

    auto PongTheGame = new GameContext();

    PongTheGame->gameLoop();

    return 0;
}