#ifndef DRONE_DECORATOR_H_
#define DRONE_DECORATOR_H_

#include "Drone.h"
#include "IEntityDecorator.h"
#include "Robot.h"

class DroneDecorator : public IEntityDecorator<Drone> {
 public:
  DroneDecorator(Drone* d) : IEntityDecorator(d) {}
  virtual void getNextDelivery() { return sub->getNextDelivery(); };
  virtual Package* getPackage() { return sub->getPackage(); };
  virtual Drone* getSub() { return sub; };
};

#endif