#include "DroneDamageDecorator.h"

DroneDamageDecorator::DroneDamageDecorator(Drone* d) : DroneDecorator(d) {
  auto* decoration = dynamic_cast<DroneDecorator*>(d);
  if (decoration) {
    original_drone = decoration->getSub();
  }
  else {
    throw std::invalid_argument("Drone is not properly wrapped");
  }
  damageFactor = 0.1;
  timeAccumulator = 0;
}

void DroneDamageDecorator::update(double dt) {

  this->timeAccumulator += dt;
  if (timeAccumulator >= 1) {
    original_drone->updateDurability(damageFactor);
    timeAccumulator = 0;
  }
  sub->update(dt);
}