#include "WeatherControl.h"

WeatherControl::WeatherControl() {
  updateInterval = 1;
  timeAccumulator = 0;
  notificationCounter = 0;
  notificationCooldown = 20;
  windResetAccumulator = 0;
  windResetInterval = 600;
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
  this->windResetAccumulator += dt;
  if (timeAccumulator >= updateInterval) {
    this->updateWind();
    timeAccumulator = 0;
    ++notificationCounter;
  }
  if (windResetAccumulator >= windResetInterval) {
    wind = {0,0,0};
    windResetAccumulator = 0;
  }
}

double WeatherControl::enforceBounds(double val) {
  if (val < -200) return -200;
  if (val > 200) return 200;
  return val;
}

void WeatherControl::updateWind() {
  double sigma = 3.0;

  std::random_device rand;
  std::mt19937 fastGenerator(rand());
  std::normal_distribution<double> normalDistribution(0.0, sigma);

  Vector3 delta_wind(normalDistribution(fastGenerator), 0,
                     normalDistribution(fastGenerator));

  wind = wind + delta_wind;

  for (int i = 0; i < 3; ++i) wind[i] = enforceBounds(wind[i]);

  if (notificationCounter >= notificationCooldown) {
    notifyObservers(generateMessage());
    notificationCounter = 0;
  }
}

std::string WeatherControl::generateMessage() {
  double vertical = wind.z;
  double horizontal = wind.x;
  // [(pixels per second) / (pixels per mile)] * (60 seconds per mile) = mph
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
  return "Current Wind: " + std::to_string((int)std::ceil(speed)) + " mph " +
         wind_direction;
}

Vector3 WeatherControl::getWind() { return wind; }