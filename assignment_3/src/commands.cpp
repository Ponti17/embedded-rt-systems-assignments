#include "commands.h"
#include <iostream>
#include "states.h"

namespace commands {

    Command::Command(State** state) : _state(state) {}

    CommandResume::CommandResume(State** state) : Command(state) {}

    void CommandResume::execute() {
        *_state = states::operational::RealTimeLoop::getInstance(); // Transition to RealTimeLoop
        std::cout << "Resuming to RealTimeLoop state.\n";
    }

    CommandStop::CommandStop(State** state) : Command(state) {}

    void CommandStop::execute() {
        *_state = states::operational::Ready::getInstance(); // Transition to Ready
        std::cout << "Stopping and transitioning to Ready state.\n";
    }

}
