#ifndef PUBLISHER_H_ 
#define PUBLISHER_H_ 

#include <vector>
#include "math/vector3.h"
#include "Observer.h"

class Observer;

class Publisher{
public:
    Publisher() {};
    virtual ~Publisher() {} 
    void addDroneObserver(Observer* o) {
        reaper = o;
    }
    void removeDroneObserver() {
        reaper = nullptr;
    }
    void notifyDroneObserver(const Vector3& pos) const {
        if (reaper) {
            reaper->notifyPosition(pos, this);
        }
    }
private:
    Observer* reaper = nullptr;
};

#endif

