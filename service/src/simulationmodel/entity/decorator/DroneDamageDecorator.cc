#include "DroneDamageDecorator.h"

#include "WeatherControl.h"

DroneDamageDecorator::DroneDamageDecorator(Drone* d) : DroneDecorator(d) {
  auto* decoration = dynamic_cast<DroneDecorator*>(d);
  if (decoration) {
    original_drone = decoration->getSub();
  } else {
    throw std::invalid_argument("Drone is not properly wrapped");
  }
  damageFactor = 0.001;
  timeAccumulator = 0;
}

void DroneDamageDecorator::update(double dt) {
  this->timeAccumulator += dt;
  if (timeAccumulator >= 1) {
    WeatherControl* w = WeatherControl::GetInstance();
    double windMagnitude = w->getWind().magnitude();
    double damage = damageFactor * windMagnitude;

    original_drone->updateDurability(damage);
    original_drone->updateSpeedBasedOnDurability();
    timeAccumulator = 0;
  }
  sub->update(dt);
}