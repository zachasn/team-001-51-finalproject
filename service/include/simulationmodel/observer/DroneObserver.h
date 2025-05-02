#ifndef DRONE_OBSERVER_H_ 
#define DRONE_OBSERVER_H_ 

#include "IObserver.h"
#include <string>
#include <iostream> 
#include "math/vector3.h"
#include "DronePublisher.h"
#include "IEntity.h"

class DronePublisher;
class Drone;

class DroneObserver {
public:
    DroneObserver() {}
    virtual ~DroneObserver() {}
    virtual void notifyPosition(const Vector3& location, const Drone* d) = 0;
};

#endif