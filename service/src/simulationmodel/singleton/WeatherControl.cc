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
    if (timeAccumulator >= updateInterval) {
        this->updateWind();
        timeAccumulator = 0;
    }
}

double enforce_bounds(double val) {
  if (val < -200) return -200;
  if (val > 200) return 200;
  return val;
}

void WeatherControl::updateWind() {

  double sigma = 3.0;

  std::random_device rand;
  std::mt19937 fast_gen(rand());
  std::normal_distribution<double> normal_dist(0.0, sigma);

  Vector3 delta_wind(normal_dist(fast_gen), 0, normal_dist(fast_gen));

  wind = wind + delta_wind;

  for (int i = 0; i < 3; ++i)
    wind[i] = enforce_bounds(wind[i]);

  std::cout << "current wind vector: " << wind << std::endl;
}