#include "WeatherControl.h"

WeatherControl::WeatherControl() {
  updateInterval = 1;
  timeAccumulator = 0;
  notificationAccumulator = 0;
  notificationInterval = 20;
  windResetAccumulator = 0;
  windResetInterval = 600;
  wind = {0, 0, 0};
}

WeatherControl* WeatherControl::weatherControl_ = nullptr;

WeatherControl* WeatherControl::GetInstance() {
  if (weatherControl_ == nullptr) {
    weatherControl_ = new WeatherControl();
  }
  return weatherControl_;
}

void WeatherControl::update(double dt) {
  timeAccumulator += dt;
  windResetAccumulator += dt;
  if (timeAccumulator >= updateInterval) {
    updateWind();
    timeAccumulator = 0;
    ++notificationAccumulator;
  }
  if (windResetAccumulator >= windResetInterval) {
    wind = {0, 0, 0};
    windResetAccumulator = 0;
    notifyObservers("The wind has settled.");
  }
}

double WeatherControl::enforceBounds(double val) {
  if (val < -200) return -200;
  if (val > 200) return 200;
  return val;
}

void WeatherControl::updateWind() {
  double sigma = 4.0;

  std::random_device rand;
  std::mt19937 fastGenerator(rand());
  std::normal_distribution<double> normalDistribution(0.0, sigma);

  Vector3 delta_wind(normalDistribution(fastGenerator), 0,
                     normalDistribution(fastGenerator));

  wind = wind + delta_wind;

  for (int i = 0; i < 3; ++i) wind[i] = enforceBounds(wind[i]);

  if (notificationAccumulator >= notificationInterval) {
    notifyObservers(generateWindDescription());
    notificationAccumulator = 0;
  }
}

std::string WeatherControl::generateWindDescription() {
  // [[(pixels per second) / (pixels per mile)]
  //    * (3600 seconds per hour)] / 10 scaling factor = mph
  double speed = ((wind.magnitude() / 1625.0) * 360);

  std::string v_direction = (wind.z >= 0) ? "South" : "North";
  std::string h_direction = (wind.x >= 0) ? "East" : "West";
  std::string wind_direction;

  if (std::fabs(wind.z) > 2 * std::fabs(wind.x)) {
    wind_direction = v_direction;
  } else if (std::fabs(wind.x) > 2 * std::fabs(wind.z)) {
    wind_direction = h_direction;
  } else {
    wind_direction = v_direction + "-" + h_direction;
  }
  return "Current Wind: " + std::to_string(static_cast<int>(std::ceil(speed))) +
         " mph " + wind_direction;
}

Vector3 WeatherControl::getWind() const { return wind; }