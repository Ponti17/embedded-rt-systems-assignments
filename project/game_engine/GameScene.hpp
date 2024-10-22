#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Types.hpp"
#include "GameObject.hpp"

#include <vector>

namespace Engine {

  
  class GameScene {

    public:
      std::vector<GameObject *> gameObjects;

      void update(float deltaTime) {

        for (auto &gameObject : gameObjects) {
            
            gameObject->update(deltaTime);
            
        }
        
      }

      void render() {

          for (auto & gameObject : gameObjects) {

            gameObject->render();

          }

      }

      void addGameObject(GameObject * gameObject) {

        gameObjects.push_back(gameObject);

      }


  };

}

#endif