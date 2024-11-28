#ifndef EMBEDDED_SYSTEM_X_H
#define EMBEDDED_SYSTEM_X_H

#include "states.h"
#include "commands.h"

#include <iostream>

class State;
class EmbeddedSystemX {

private:
    State* state;

public:
    EmbeddedSystemX();

    void changeState(State* nextState);
    void selfTestOk();
    void selfTestFailed(int errorNo);
    void restart();
    void exit();
    void initialized();
    void configure();
    void configurationEnded();
    void start();
    void stop();
    void suspend();
    void resume();

    void displayError(int errorNo);

};

#endif