#ifndef COMMANDS_H
#define COMMANDS_H

#include "states.h"

class State;

class Command {
public:
    Command(State** state);
    virtual void execute() = 0;
    virtual ~Command() = default;
protected:
    State** _state; 
};

class CommandResume : public Command {
public:
    CommandResume(State** state);
    void execute() override;
};

class CommandStop : public Command {
public:
    CommandStop(State** state);
    void execute() override;
};


#endif
