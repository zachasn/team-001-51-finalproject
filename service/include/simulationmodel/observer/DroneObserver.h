#ifndef DRONE_OBSERVER_H_
#define DRONE_OBSERVER_H_

#include <iostream>
#include <string>

#include "DronePublisher.h"
#include "IEntity.h"
#include "IObserver.h"
#include "math/vector3.h"

class DronePublisher;
class Drone;

class DroneObserver {
 public:
  DroneObserver() {}
  virtual ~DroneObserver() {}
  virtual void notifyPosition(const Vector3& location, Drone* d) = 0;
};

#endif