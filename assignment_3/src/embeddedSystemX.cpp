#include "embeddedSystemX.h"


EmbeddedSystemX::EmbeddedSystemX() {
    state = PowerOnSelfTest::getInstance();
}

void EmbeddedSystemX::changeState(State* nextState) {

    std::cout << "Current state\tNext state\n"
    << state->getStateName() << "\t" 
    << nextState->getStateName() 
    << "\n " << std::endl;
    
    state = nextState;

}

void EmbeddedSystemX::selfTestOk() {
    state->selfTestOk(this);
}

void EmbeddedSystemX::selfTestFailed(int errorNo) {
    state->selfTestFailed(this, errorNo);
}

void EmbeddedSystemX::restart() {
    state->restart(this);
}

void EmbeddedSystemX::exit() {
    state->exit(this);
}

void EmbeddedSystemX::initialized() {
    state->initialized(this);
}

void EmbeddedSystemX::configure() {
    state->configure(this);
}

void EmbeddedSystemX::configurationEnded() {
    state->configurationEnded(this);
}

void EmbeddedSystemX::start() {
    state->start(this);
}

void EmbeddedSystemX::stop() {
    CommandStop req(&(this->state));
    req.execute();
}

void EmbeddedSystemX::resume() {
    CommandResume req(&(this->state));
    req.execute();
}

void EmbeddedSystemX::suspend() {
    state->suspend(this);
}

void EmbeddedSystemX::displayError(int errorNo) {
    std::cout << "Error: " << errorNo << std::endl;
}





