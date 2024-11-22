#include "states.h"

using namespace states;

PowerOnSelfTest* PowerOnSelfTest::instance = nullptr;

void PowerOnSelfTest::selfTestOk(EmbeddedSystemX* context) {
    context->changeState(Initializing::getInstance());
} 