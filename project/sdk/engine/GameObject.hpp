#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Types.hpp"
#include "Shape.hpp"

namespace Engine {

	class GameObject {

  		public:

			GameObject(): model(nullptr) {}

		    Vec2f position;
	        Vec2f velocity;
            Shape * model;
			virtual void update(float deltaTime) = 0;
			virtual void render() = 0;
	};

}

#endif
