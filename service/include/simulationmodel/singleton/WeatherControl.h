#ifndef WEATHER_CONTROL_H
#define WEATHER_CONTROL_H

class WeatherControl {
 protected:
  WeatherControl() {
    updateInterval = 1;
    timeAccumulator = 0;
  }

  static WeatherControl* weatherControl_;

  double updateInterval;
  double timeAccumulator;

 public:
  WeatherControl(WeatherControl& other) = delete;

  void operator=(const WeatherControl&) = delete;

  static WeatherControl* GetInstance(const std::string& value);

};

WeatherControl* WeatherControl::weatherControl_ = nullptr;

WeatherControl* WeatherControl::GetInstance(const std::string& value) {
  if (weatherControl_ == nullptr) {
    weatherControl_ = new Singleton(value);
  }
  return weatherControl_;
}

#endif