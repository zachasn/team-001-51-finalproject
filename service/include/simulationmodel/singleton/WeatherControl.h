#ifndef WEATHER_CONTROL_H_
#define WEATHER_CONTROL_H_

#include <cmath>
#include <iostream>
#include <random>
#include <string>

#include "../math/vector3.h"
#include "IPublisher.h"

class WeatherControl : public IPublisher {
 private:
  WeatherControl();
  ~WeatherControl() = default;

  static WeatherControl* weatherControl_;

  // Helper functions
  double enforceBounds(double val);
  std::string generateWindDescription();
  void updateWind();

  // Member variables
  double timeAccumulator;
  double updateInterval;
  int notificationAccumulator;
  int notificationInterval;
  double windResetAccumulator;
  double windResetInterval;
  Vector3 wind;

 public:
  WeatherControl(WeatherControl& other) = delete;
  void operator=(const WeatherControl&) = delete;

  static WeatherControl* GetInstance();

  void update(double dt);

  Vector3 getWind() const;
};

#endif