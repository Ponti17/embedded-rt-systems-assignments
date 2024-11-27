#include "states.h"
#include "embeddedSystemX.h"
#include "commands.h"

#include <iostream>


int main(int argc, char const *argv[])
{
    
    std::cout << "Test program..." << std::endl;

    EmbeddedSystemX system;

    system.selfTestOk();
    system.initialized();
    system.configure();
    system.configurationEnded();
    system.start();
    system.suspend();
    system.resume();
    system.stop();


    return 0;
}