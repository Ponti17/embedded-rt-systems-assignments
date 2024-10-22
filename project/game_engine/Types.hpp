//
// Created by alext on 22/10/2024.
//

#ifndef TYPES_H
#define TYPES_H

namespace Engine {

    struct Vec2 {

        int x, y;
        Vec2() : x(0), y(0) {}
        Vec2(int x, int y) : x(x), y(y) {}

        Vec2 operator+(const Vec2& other) {
            return {x + other.x, y + other.y};
        }
        Vec2 operator*(const int& other) {
            return {x * other, y * other};
        }

    };

    struct Vec2f {

        float x, y;

        Vec2f(float x, float y) : x(x), y(y) {}
        Vec2f() : x(0.0f), y(0.0f) {}
        
        Vec2f operator+(const Vec2f& other) {
            return {x + other.x, y + other.y};
        }
        Vec2f operator*(const float& other) {
            return {x * other, y * other};
        }

        Vec2 convertToVec2() {
            return Vec2(static_cast<int>(x), static_cast<int>(y));
        }
        
    };

} // Engine

#endif //TYPES_H
