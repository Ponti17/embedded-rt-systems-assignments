#include "states.h"

using namespace states;
using namespace states::operational;

// Singleton instances
PowerOnSelfTest* PowerOnSelfTest::instance = nullptr;
Failure* Failure::instance = nullptr;
Initializing* Initializing::instance = nullptr;
Ready* Ready::instance = nullptr;
Configuration* Configuration::instance = nullptr;
RealTimeLoop* RealTimeLoop::instance = nullptr;
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



