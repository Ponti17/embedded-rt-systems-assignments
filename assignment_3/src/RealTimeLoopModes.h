#ifndef REALTIMELOOPMODES_H
#define REALTIMELOOPMODES_H

#include "states.h"


class RealTimeLoop;

class RealTimeLoopMode {

    virtual void chMode1(RealTimeLoop * realTimeLoop);
    virtual void chMode2(RealTimeLoop * realTimeLoop);
    virtual void chMode3(RealTimeLoop * realTimeLoop);

    virtual void chMode(RealTimeLoop * realTimeLoop) {};

    virtual void eventX();

};



class Mode1;
class Mode2;
class Mode3;

class Mode1 : public RealTimeLoopMode {
    
    private:
        static Mode1* instance;
        Mode1(){};
    public:
        static Mode1* getInstance() {
            if(instance == nullptr) {
                
                instance = new Mode1();

            }

            return instance;
        }

        void chMode2(RealTimeLoop * realTimeLoop) override;
        void chMode(RealTimeLoop * realTimeLoop) override;
        void eventX() override;

};

class Mode2 : public RealTimeLoopMode {
    
    private:
        static Mode2* instance;
        Mode2(){};
    public:
        static Mode2* getInstance() {
            if(instance == nullptr) {
                
                instance = new Mode2();

            }

            return instance;
        }
        void chMode3(RealTimeLoop * realTimeLoop) override;
        void chMode(RealTimeLoop * realTimeLoop) override;
        void eventX() override;
};

class Mode3 : public RealTimeLoopMode {
    
    private:
        static Mode3* instance;
        Mode3(){};
    public:
        static Mode3* getInstance() {
            if(instance == nullptr) {
                
                instance = new Mode3();

            }

            return instance;
        }
        void chMode1(RealTimeLoop * realTimeLoop) override;
        void chMode(RealTimeLoop * realTimeLoop) override;
        void eventX() override;

};

#endif