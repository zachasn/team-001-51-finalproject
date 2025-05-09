// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation

#ifndef WEATHER_CONTROL_H_
#define WEATHER_CONTROL_H_

#include <cmath>
#include <iostream>
#include <random>
#include <string>

#include "../math/vector3.h"
#include "IPublisher.h"

/**
 * @class WeatherControl
 * @brief Singleton class which simulates and controls dynamic wind simulation.
 *
 * WeatherControl provides wind updates over time and notifies the simulation of
 * changes. Weather control implements the Singleton design pattern and inherits
 * from IPublisher to support the observer pattern as well for weather related
 * notifications.
 */
class WeatherControl : public IPublisher {
 private:
  /**
   * @brief Private default constructor to enforce singleton pattern.
   */
  WeatherControl();
  /**
   * @brief Default destructor.
   */
  ~WeatherControl() = default;

  /// Static pointer to the singleton instance of WeatherControl.
  static WeatherControl* weatherControl_;

  /**
   * @brief Restricts the given value within [-200, 200].
   * @param val The value to restrict.
   * @return Restricted value now within range [-200, 200].
   */
  double enforceBound200(double val);

  /**
   * @brief Generates a description of the current wind conditions.
   * @return A string describing the wind's direction and magnitude.
   */
  std::string generateWindDescription();

  /**
   * @brief Updates the wind vector with new randomized values.
   */
  void updateWind();

  /// Accumulated time since the last wind update.
  double timeAccumulator;

  /// Time interval after which the weather should be updated.
  double updateInterval;

  /// Accumulated time since last notification.
  int notificationAccumulator;

  /// Interval of notification frequency.
  int notificationInterval;

  /// Accumulated time since the last total wind reset.
  double windResetAccumulator;

  /// Time interval after which wind conditions are reset.
  double windResetInterval;

  /// Current wind vector.
  Vector3 wind;

 public:
  /**
   * @brief Deleted copy constructor to prevent copying.
   */
  WeatherControl(WeatherControl& other) = delete;

  /**
   * @brief Deleted assignment operator to prevent copying.
   */
  void operator=(const WeatherControl&) = delete;

  /**
   * @brief Retrieves the singleton instance of WeatherControl.
   * @return Pointer to the WeatherControl instance.
   */
  static WeatherControl* GetInstance();

  /**
   * @brief Updates the weather simulation over time.
   * @param dt Delta time since the last update.
   */
  void update(double dt);

  /**
   * @brief Gets the current wind vector.
   * @return The current wind as a Vector3.
   */
  Vector3 getWind() const;
};

#endif
