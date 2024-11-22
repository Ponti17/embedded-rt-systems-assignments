#ifndef EMBEDDED_SYSTEM_X_H
#define EMBEDDED_SYSTEM_X_H

#include "states.h"

class EmbeddedSystemX {

private:
    State* state;

public:
    EmbeddedSystemX();

    void changeState(State* nextState);
    void selfTestOk();
    void selfTestFailed(int errno);
    void displayError(int errno);

};

#endif