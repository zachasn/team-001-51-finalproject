#include "WeatherControl.h"

WeatherControl::WeatherControl() {
  updateInterval = 1;
  timeAccumulator = 0;
  notificationCooldown = 0;
  Vector3 wind = {0, 0, 0};
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
    ++notificationCooldown;
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

  for (int i = 0; i < 3; ++i) wind[i] = enforce_bounds(wind[i]);

  if (notificationCooldown >= 20) {
    double vertical = wind.z;
    double horizontal = wind.x;
    double speed = (wind.magnitude() / 1625.0) * 60;

    std::string v_direction;
    std::string h_direction;
    std::string wind_direction;

    if (vertical >= 0) {
      v_direction = "South";
    } else {
      v_direction = "North";
    }
    if (horizontal >= 0) {
      h_direction = "East";
    } else {
      h_direction = "West";
    }

    if (std::fabs(vertical) > 2 * std::fabs(horizontal)) {
      wind_direction = v_direction;
    } else if (std::fabs(horizontal) > 2 * std::fabs(vertical)) {
      wind_direction = h_direction;
    } else {
      wind_direction = v_direction + "-" + h_direction;
    }

    notifyObservers("Current Wind: " + std::to_string((int)std::ceil(speed)) +
                    " mph " + wind_direction);
    notificationCooldown = 0;
    
  }
}