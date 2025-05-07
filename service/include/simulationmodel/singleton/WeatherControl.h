#ifndef WEATHER_CONTROL_H_
#define WEATHER_CONTROL_H_

#include <cmath>
#include <iostream>
#include <random>
#include <string>

#include "../math/vector3.h"
#include "IPublisher.h"

class WeatherControl : public IPublisher {
 protected:
  WeatherControl();

  double enforceBounds(double val);
  std::string generateMessage();
  void updateWind();

  static WeatherControl* weatherControl_;
  double updateInterval;
  double timeAccumulator;
  int notificationCounter;
  int notificationCooldown;
  Vector3 wind;

 public:
  WeatherControl(WeatherControl& other) = delete;

  void operator=(const WeatherControl&) = delete;

  static WeatherControl* GetInstance();

  void update(double dt);
  
  Vector3 getWind();
};

#endif