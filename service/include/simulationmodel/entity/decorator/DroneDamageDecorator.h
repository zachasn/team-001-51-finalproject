#ifndef DRONE_DAMAGE_DECORATOR_H
#define DRONE_DAMAGE_DECORATOR_H

#include "Drone.h"
#include "DroneDecorator.h"
#include "Package.h"

class DroneDamageDecorator : public DroneDecorator {
 private:
  double damageFactor = 0;
  double timeAccumulator = 0;

 public:
  DroneDamageDecorator(Drone* d);
  void update(double dt);
};

#endif  // DRONE_DAMAGE_DECORATOR_H