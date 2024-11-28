#include "commands.h"
#include <iostream>
#include "states.h"


Command::Command(State** state) : _state(state) {}

CommandResume::CommandResume(State** state) : Command(state) {}

void CommandResume::execute() {
    *_state = RealTimeLoop::getInstance(); // Transition to RealTimeLoop
    std::cout << "Resuming to RealTimeLoop state.\n";
}

CommandStop::CommandStop(State** state) : Command(state) {}

void CommandStop::execute() {
    *_state = Ready::getInstance(); // Transition to Ready
    std::cout << "Stopping and transitioning to Ready state.\n";
}

