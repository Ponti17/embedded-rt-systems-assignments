#include "states.h"

using namespace states;

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

void PowerOnSelfTest::selfTestFailed(EmbeddedSystemX* context, int errno) {
    context->displayError(errno);
    context->changeState(Failure::getInstance());
}

