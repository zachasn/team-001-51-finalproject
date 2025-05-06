#ifndef WEATHER_CONTROL_H_
#define WEATHER_CONTROL_H_

#include "../math/vector3.h"
#include <iostream>
#include <random>

class WeatherControl {
 protected:
  WeatherControl();

  static WeatherControl* weatherControl_;

  double updateInterval;
  double timeAccumulator;
  Vector3 wind;

 public:
  WeatherControl(WeatherControl& other) = delete;

  void operator=(const WeatherControl&) = delete;

  static WeatherControl* GetInstance();

  void update(double dt);
  void updateWind();

};

#endif