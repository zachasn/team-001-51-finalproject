#ifndef DRONE_PUBLISHER_H_ 
#define DRONE_PUBLISHER_H_ 

#include <vector>
#include "math/vector3.h"
#include "DroneObserver.h"

class DroneObserver;

class DronePublisher{
public:
    DronePublisher() {
        std::cout << "DronePublisher created" << std::endl;
    }
    //virtual ~DronePublisher() = 0;
    void addDroneObserver(DroneObserver* o) {
        reaper = o;
    }
    void removeDroneObserver() {
        reaper = nullptr;
    }
    DroneObserver* getReaper() {
        return reaper;
    }

    virtual void notifyDroneObserver(const Vector3& pos) = 0;
private:
    DroneObserver* reaper = nullptr;
};

#endif

