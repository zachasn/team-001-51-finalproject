#ifndef WEATHER_CONTROL_H_
#define WEATHER_CONTROL_H_

#include <iostream>
#include <random>
#include <string>
#include <cmath>

#include "../math/vector3.h"
#include "IPublisher.h"

class WeatherControl : public IPublisher {
 protected:
  WeatherControl();

  static WeatherControl* weatherControl_;
  double updateInterval;
  double timeAccumulator;
  int notificationCooldown;
  Vector3 wind;

 public:
  WeatherControl(WeatherControl& other) = delete;

  void operator=(const WeatherControl&) = delete;

  static WeatherControl* GetInstance();

  void update(double dt);
  void updateWind();
  Vector3 getWind() { return wind; }
};

#endif