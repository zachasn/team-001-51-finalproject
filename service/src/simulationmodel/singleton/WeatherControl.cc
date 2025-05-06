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

  double sigma = 1.0;

  std::random_device rand;
  std::mt19937 fast_gen(rand());
  std::normal_distribution<double> normal_dist(0.0, sigma);

  Vector3 delta_wind(normal_dist(fast_gen), normal_dist(fast_gen), 0);

  wind = wind + delta_wind;

  // std::cout << "current wind vector: " << wind << std::endl;
}