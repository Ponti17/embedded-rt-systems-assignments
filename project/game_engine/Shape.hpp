//
// Created by alext on 22/10/2024.
//

#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace Engine {

class Shape {
public:
  virtual void draw() = 0;
};

class Circle : public Shape {


}; // Engine

class Rectrangle : public Shape {

}; // Engine

} // Engine

#endif //SHAPE_HPP
