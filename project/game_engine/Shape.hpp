#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace Engine {

	class Shape {
		public:
		virtual void draw() = 0;
	};

namespace Shapes {

		class Circle : public Shape {
			
			float radius;

			Circle(float radius) : radius(radius) {}

			void draw() override {
				
				//todo: GPU API CALL

			}

		};

		class Rectrangle : public Shape {

			int width, height;

			Rectrangle(int width, int height) : width(width), height(height) {}

			void draw() override {

				//todo: GPU API CALL 

			}

		};
	}
}

#endif
