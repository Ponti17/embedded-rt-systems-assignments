#ifndef COMMANDS_H
#define COMMANDS_H

#include "embeddedSystemX.h"

class Command {

public:

    virtual void execute(EmbeddedSystemX* context) = 0;
    virtual ~Command() = default;
    
};


#endif