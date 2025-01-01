#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "types.hpp"

namespace Engine {

    class Shape {
    public:
        virtual void draw(Vec2 position) = 0;  // Pure virtual function for drawing
    };

    namespace Shapes2D {

        class Circle : public Shape {
        public:
            float radius;

           
            Circle(float radius) : radius(radius) {}

            void draw(Vec2 position) override {
                // TODO: GPU API CALL for Circle
            }
        };

        class Rectangle : public Shape {
        public:
            int width, height;

            
            Rectangle(int width, int height) : width(width), height(height) {}

            void draw(Vec2 position) override {
                // TODO: GPU API CALL for Rectangle
            }
        };

    } // namespace Shapes2D
} // namespace Engine

#endif // SHAPE_HPP
