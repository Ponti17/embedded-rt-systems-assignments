#ifndef STATES_H
#define STATES_H

#include "embeddedSystemX.h"

class State {
public:
    // Triggable events
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

    virtual ~State() = default;
};

namespace states {

    // Forward declarations of state classes
    class PowerOnSelfTest;
    class Failure;
    class Initializing;
    class Ready;
    class Configuration;
    class RealTimeLoop;
    class Suspended;



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


        void selfTestOk(EmbeddedSystemX* context) override;
        void selfTestFailed(EmbeddedSystemX* context, int errno) override;


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

        void initialized(EmbeddedSystemX* context) override;
    };

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

        void configurationEnded(EmbeddedSystemX* context) override;

    };

    class RealTimeLoop : public State {

    private:
        static RealTimeLoop* instance;
        RealTimeLoop(){};

    public:
        static RealTimeLoop* getInstance() {
            if(instance == nullptr) {
                
                instance = new RealTimeLoop();

            }

            return instance;
        }

        void stop(EmbeddedSystemX* context) override;
        void suspend(EmbeddedSystemX* context) override;

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

        void resume(EmbeddedSystemX* context) override;
        void stop(EmbeddedSystemX* context) override;

    };
}
#endif