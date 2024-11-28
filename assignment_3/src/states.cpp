#include "states.h"

// Singleton instances
PowerOnSelfTest* PowerOnSelfTest::instance = nullptr;
Failure* Failure::instance = nullptr;
Initializing* Initializing::instance = nullptr;
Ready* Ready::instance = nullptr;
Configuration* Configuration::instance = nullptr;
RealTimeLoop* RealTimeLoop::instance = nullptr;
RealTimeLoopMode* RealTimeLoop::state_mode = nullptr;
Suspended* Suspended::instance = nullptr;


void PowerOnSelfTest::selfTestOk(EmbeddedSystemX* context) {
    context->changeState(Initializing::getInstance());
}   

void PowerOnSelfTest::selfTestFailed(EmbeddedSystemX* context, int errorNo) {
    context->displayError(errorNo);
    context->changeState(Failure::getInstance());
}

void Failure::restart(EmbeddedSystemX* context) {
    context->changeState(Initializing::getInstance());
}

void Failure::exit(EmbeddedSystemX* context) {
    std::cout << "Exiting system" << std::endl;
}

void Initializing::initialized(EmbeddedSystemX* context) {
    context->changeState(Ready::getInstance());
}

void Ready::configure(EmbeddedSystemX* context) {
    context->changeState(Configuration::getInstance());
}

void Ready::start(EmbeddedSystemX* context) {
    context->changeState(RealTimeLoop::getInstance());
}

void Configuration::configurationEnded(EmbeddedSystemX* context) {
    context->changeState(Ready::getInstance());
}

void RealTimeLoop::stop(EmbeddedSystemX* context) {
    context->changeState(Ready::getInstance());
}

void RealTimeLoop::suspend(EmbeddedSystemX* context) {
    context->changeState(Suspended::getInstance());
}

void Suspended::resume(EmbeddedSystemX* context) {
    context->changeState(RealTimeLoop::getInstance());
}

void Suspended::stop(EmbeddedSystemX* context) {
    context->changeState(Ready::getInstance());
}

//real time loop
RealTimeLoop::RealTimeLoop() {
    done = false;
    state_mode = Mode1::getInstance();
    runnable = std::thread([=] {dispatch();});
} 

void RealTimeLoop::chMode() {
    state_mode->chMode(this);
}

void RealTimeLoop::changeMode(RealTimeLoopMode * nextMode) {
    state_mode = nextMode;
}

void RealTimeLoop::eventX() {
    state_mode->eventX();
}

void RealTimeLoop::dispatch() {
    while (!done) {
        auto operation = dispatchQueue.remove();
        operation();
    }
}

RealTimeLoop::~RealTimeLoop() {
    dispatchQueue.insert(
        [&]() { done = true; }
    );
    runnable.join();
}

void RealTimeLoop::restart(EmbeddedSystemX* context) {
    context->changeState(Initializing::getInstance());
}