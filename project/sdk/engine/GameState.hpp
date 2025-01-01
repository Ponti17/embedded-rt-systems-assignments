//
// Created by alext on 22/10/2024.
//

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "GameScene.hpp"
#include "Types.hpp"

namespace Engine {

class GameState {
      
public:
      GameScene * currentScene;
      
      void update(float deltaTime) {
        
        currentScene->update(deltaTime);
        
      }

      void render() {
        
        currentScene->render();
        
      }

};

} // Engine

#endif //GAMESTATE_HPP