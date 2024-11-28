#ifndef STATES_H
#define STATES_H

#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <future>

#include "embeddedSystemX.h"
#include "RealTimeLoopModes.h"

using std::string;

class EmbeddedSystemX;
class RealTimeLoopMode;

class State {

public:
    // Triggable events
    virtual void selfTestOk(EmbeddedSystemX* context){};
    virtual void selfTestFailed(EmbeddedSystemX* context, int errorNo){};
    virtual void restart(EmbeddedSystemX* context){};
    virtual void exit(EmbeddedSystemX* context){};
    virtual void initialized(EmbeddedSystemX* context){};
    virtual void configure(EmbeddedSystemX* context){};
    virtual void configurationEnded(EmbeddedSystemX* context){};
    virtual void start(EmbeddedSystemX* context){};
    virtual void stop(EmbeddedSystemX* context){};
    virtual void suspend(EmbeddedSystemX* context){};
    virtual void resume(EmbeddedSystemX* context){};

    virtual string getStateName() const = 0;

    virtual ~State() = default;

};



// Forward declarations of state classes
class PowerOnSelfTest;
class Failure;
class Initializing;

class PowerOnSelfTest : public State {

private: 
    static PowerOnSelfTest* instance;
    PowerOnSelfTest(){};

public:
    static PowerOnSelfTest* getInstance() {
        if(instance == nullptr) {
            
            instance = new PowerOnSelfTest();

        }

        return instance;
    }

    string getStateName() const override {
        return "PowerOnSelfTest";
    }


    void selfTestOk(EmbeddedSystemX* context) override;
    void selfTestFailed(EmbeddedSystemX* context, int errorNo) override;


};

class Failure : public State {

private:
    static Failure* instance;
    Failure(){};

public:
    static Failure* getInstance() {
        if(instance == nullptr) {
            
            instance = new Failure();

        }

        return instance;
    }

    string getStateName() const override {
        return "Failure";
    }

    void restart(EmbeddedSystemX* context) override;
    void exit(EmbeddedSystemX* context) override;
};

class Initializing : public State {
private:
    static Initializing* instance;
    Initializing(){};

public:
    static Initializing* getInstance() {
        if(instance == nullptr) {
            
            instance = new Initializing();

        }

        return instance;
    }
    string getStateName() const override {
        return "Initializing";
    }

    void initialized(EmbeddedSystemX* context) override;

};



class Ready;
class Configuration;
class RealTimeLoop;
class Suspended;

class Ready : public State {
private:
    static Ready* instance;
    Ready(){};

public:
    static Ready* getInstance() {
        if(instance == nullptr) {
            
            instance = new Ready();

        }

        return instance;
    }

    string getStateName() const override {
        return "Ready\t";
    }

    void configure(EmbeddedSystemX* context) override;
    void start(EmbeddedSystemX* context) override;
};

class Configuration : public State {

private:
    static Configuration* instance;
    Configuration(){};

public:
    static Configuration* getInstance() {
        if(instance == nullptr) {
            
            instance = new Configuration();

        }

        return instance;
    }

    string getStateName() const override {
        return "Configuration";
    }

    void configurationEnded(EmbeddedSystemX* context) override;

};


class Suspended : public State {

private:
    static Suspended* instance;
    Suspended(){};

public:
    static Suspended* getInstance() {
        if(instance == nullptr) {
            
            instance = new Suspended();

        }

        return instance;
    }

    string getStateName() const override {
        return "Suspended";
    }

    void resume(EmbeddedSystemX* context) override;
    void stop(EmbeddedSystemX* context) override;

};

class DispatchQueue {
    std::mutex queue_lock;
    std::queue<std::function<void()>> queue_operations;
    std::condition_variable queue_empty;
    
public:
    void insert(std::function<void()> operation) {
        std::lock_guard<std::mutex> lock(queue_lock);
        queue_operations.push(operation);
        queue_empty.notify_one();
    }

    std::function<void()> remove() {
        std::unique_lock<std::mutex> lock(queue_lock);
        queue_empty.wait(
            lock,
            [&] { return !queue_operations.empty();}
        );
        std::function<void()> operation = queue_operations.front();
        queue_operations.pop();
        return operation;
    }

};

class RealTimeLoop : public State {

private:
    static RealTimeLoop* instance;
    static RealTimeLoopMode* state_mode;
    
    RealTimeLoop();
    ~RealTimeLoop();
    
    std::atomic<bool> done;
    std::thread runnable;
    DispatchQueue dispatchQueue;

public:

    static RealTimeLoop* getInstance() {
        if(instance == nullptr) {
            
            instance = new RealTimeLoop();

        }

        return instance;
    }

    string getStateName() const override {
        return "RealTimeLoop";
    }

    void restart(EmbeddedSystemX* context) override;
    void stop(EmbeddedSystemX* context) override;
    void suspend(EmbeddedSystemX* context) override;

    void chMode();
    void changeMode(RealTimeLoopMode* nextMode);


    void dispatch();
    void eventX();
    
    DispatchQueue& getDispatchQueue();

};

#endif