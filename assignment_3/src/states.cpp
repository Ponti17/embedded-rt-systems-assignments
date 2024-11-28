#include "states.h"

// Singleton instances
PowerOnSelfTest* PowerOnSelfTest::instance = nullptr;
Failure* Failure::instance = nullptr;
Initializing* Initializing::instance = nullptr;
Ready* Ready::instance = nullptr;
Configuration* Configuration::instance = nullptr;
RealTimeLoop* RealTimeLoop::instance = nullptr;
RealTimeLoopMode* RealTimeLoop::state_mode = nullptr;
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

void DispatchQueue::insert(std::function<void()> operation) {
    {
        std::lock_guard<std::mutex> lock(queue_lock);
        queue_operations.push(operation);
    }
    queue_empty.notify_one();
    std::cout << "DispatchQueue: Inserted operation.\n";
}

std::function<void()> DispatchQueue::remove() {
    std::unique_lock<std::mutex> lock(queue_lock);
    queue_empty.wait(lock, [&] { return !queue_operations.empty(); });
    auto operation = queue_operations.front();
    queue_operations.pop();
    std::cout << "DispatchQueue: Removed operation.\n";
    return operation;
}

//real time loop
RealTimeLoop::RealTimeLoop() {
    done = false;
    state_mode = Mode1::getInstance();
    runnable = std::thread([this] {dispatch();});
} 

void RealTimeLoop::chMode() {
    state_mode->chMode(this);
}

void RealTimeLoop::changeMode(RealTimeLoopMode* nextMode) {
    state_mode = nextMode;
    std::cout << "RealTimeLoop: Changed mode to " << typeid(*state_mode).name() << std::endl;
}

void RealTimeLoop::eventX() {
    dispatchQueue.insert(
        [this]() { handleEventX(); }
    );
}

void RealTimeLoop::dispatch() {
    std::cout << "Dispatch loop started." << std::endl;
    while (!done) {
        try {
            auto operation = dispatchQueue.remove();
            if (operation) {
                operation();
            } else {
                std::cout << "Dispatch queue returned a null operation." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Dispatch encountered an error: " << e.what() << std::endl;
        }
    }
    std::cout << "Dispatch loop exited." << std::endl;
}

RealTimeLoop::~RealTimeLoop() {
    if (!done) {
        stopDispatch();  
    }
    std::cout << "RealTimeLoop destructor completed." << std::endl;
}

void RealTimeLoop::restart(EmbeddedSystemX* context) {
    context->changeState(PowerOnSelfTest::getInstance());
}

void RealTimeLoop::handleEventX() {
    if (state_mode) {
        std::cout << "RealTimeLoop: Handling eventX in " << typeid(*state_mode).name() << std::endl;
        state_mode->eventX();
    } else {
        std::cout << "RealTimeLoop: No mode set to handle eventX." << std::endl;
    }
}

void RealTimeLoop::stopDispatch() {
    done = true;
    dispatchQueue.insert([]() {}); 
    if (runnable.joinable()) {
        runnable.join();
    }
    std::cout << "Dispatch thread stopped." << std::endl;
}
