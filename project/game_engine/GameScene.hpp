//
// Created by alext on 22/10/2024.
//

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
          for (auto & object : this->gameObjects) {
            object->update(deltaTime);
            };

};

} // Engine

#endif //GAMESCENE_H