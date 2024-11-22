#ifndef STATES_H
#define STATES_H

#include "embeddedSystemX.h"

class State {

public:

    virtual void selfTestOk(EmbeddedSystemX* context){};
    virtual void selfTestFailed(EmbeddedSystemX* context, int errno){};
    virtual void restart(EmbeddedSystemX* context){};
    virtual void exit(EmbeddedSystemX* context){};
    virtual void initialized(EmbeddedSystemX* context){};
    virtual void configure(EmbeddedSystemX* context){};
    virtual void configurationEnded(EmbeddedSystemX* context){};
    virtual void start(EmbeddedSystemX* context){};
    virtual void stop(EmbeddedSystemX* context){};
    virtual void suspend(EmbeddedSystemX* context){};
    virtual void resume(EmbeddedSystemX* context){};

};

class PowerOnSelfTest : public State {



};

#endif