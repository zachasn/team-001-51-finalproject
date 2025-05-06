#include "WeatherControl.h"

WeatherControl::WeatherControl() {
    updateInterval = 1;
    timeAccumulator = 0;
    Vector3 wind = {0,0,0};
}

WeatherControl* WeatherControl::weatherControl_ = nullptr;

WeatherControl* WeatherControl::GetInstance() {
  if (weatherControl_ == nullptr) {
    weatherControl_ = new WeatherControl();
  }
  return weatherControl_;
}

void WeatherControl::update(double dt) {
    this->timeAccumulator += dt;
    if (timeAccumulator > updateInterval) {
        this->updateWind();
        timeAccumulator = 0;
    }
}

void WeatherControl::updateWind() {
    
}