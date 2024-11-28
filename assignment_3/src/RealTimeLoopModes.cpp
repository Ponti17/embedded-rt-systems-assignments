#include "RealTimeLoopModes.h"

Mode1* Mode1::instance = nullptr;
Mode2* Mode2::instance = nullptr;
Mode3* Mode3::instance = nullptr;

Mode1::Mode1() = default;
Mode2::Mode2() = default;
Mode3::Mode3() = default;


void Mode1::chMode(RealTimeLoop * realTimeLoop) {
    realTimeLoop->changeMode(Mode2::getInstance());
}

void Mode1::eventX() {
    std::cout << "Mode1 eventX" << std::endl;
}

void Mode2::chMode(RealTimeLoop * realTimeLoop) {
    realTimeLoop->changeMode(Mode3::getInstance());
}

void Mode2::eventX() {
    std::cout << "Mode2 eventX" << std::endl;
}

void Mode3::chMode(RealTimeLoop * realTimeLoop) {
    realTimeLoop->changeMode(Mode1::getInstance());
}

void Mode3::eventX() {
    std::cout << "Mode3 eventX" << std::endl;
}