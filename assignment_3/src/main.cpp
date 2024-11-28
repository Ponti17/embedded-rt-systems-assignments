#include "states.h"
#include "embeddedSystemX.h"
#include "commands.h"
#include "RealTimeLoopModes.h"

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

    std::cout << "Testing RealTimeLoop Active Object..." << std::endl;

    auto* realTimeLoop = RealTimeLoop::getInstance();

    std::cout << "Triggering eventX in Mode1..." << std::endl;
    realTimeLoop->eventX();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 

    std::cout << "Switching to Mode2..." << std::endl;
    realTimeLoop->changeMode(Mode2::getInstance());
    std::cout << "Triggering eventX in Mode2..." << std::endl;
    realTimeLoop->eventX();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Switching to Mode3..." << std::endl;
    realTimeLoop->changeMode(Mode3::getInstance());
    std::cout << "Triggering eventX in Mode3..." << std::endl;
    realTimeLoop->eventX();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "Stopping RealTimeLoop dispatch thread..." << std::endl;
    realTimeLoop->stopDispatch();

    std::cout << "All tests completed." << std::endl;


    return 0;
}

