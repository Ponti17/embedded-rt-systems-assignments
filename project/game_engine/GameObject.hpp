#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Types.hpp"
#include "Shape.hpp"

namespace Engine {

	class GameObject {

  		public:
		    Vec2 position;
	        Vec2 velocity;
            Shape * model;
			virtual void update(float deltaTime) = 0;
			virtual void render() = 0;
	};

}

#endif
