#ifndef DRONE_DAMAGE_DECORATOR_H
#define DRONE_DAMAGE_DECORATOR_H

#include "Drone.h"
#include "DroneDecorator.h"
#include "DroneColorDecorator.h"
#include "Package.h"

class DroneDamageDecorator : public DroneDecorator {
 private:
  double damageFactor;
  double timeAccumulator;
  Drone* original_drone;

 public:
  DroneDamageDecorator(Drone* d);
  void update(double dt);
};

#endif  // DRONE_DAMAGE_DECORATOR_H