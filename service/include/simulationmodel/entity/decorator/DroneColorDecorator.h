#ifndef DRONE_COLOR_DECORATOR_H
#define DRONE_COLOR_DECORATOR_H

#include "Drone.h"
#include "DroneDecorator.h"
#include "Package.h"

/**
 * @class DroneColorDecorator
 * @brief Decorator class to dynamically change the drone's color based on its
 * delivery progress and current durability.
 */
class DroneColorDecorator : public DroneDecorator {
 private:
  double hue = 0;
  double saturation = 0;
  double light = 0;
  double distToPackage = -1;
  double distToDestination = -1;

 public:
  /**
   * @brief Default constructor
   */
  DroneColorDecorator(Drone* d, double = 0, double = 0, double = 0);

  /**
   * @brief Destructor for DroneColorDecorator.
   */
  virtual ~DroneColorDecorator() = default;

  /**
   * @brief Gets the current color of the drone
   * @return The current color of the drone
   */
  std::string getColor() const;

  /**
   * @brief Sets the color (hue, saturation, light) of the drone
   * @param h double representing hue
   * @param s double representing saturation
   * @param l double representing light
   */
  void setColor(double h, double s, double l);

  /**
   * @brief Updates the drone’s state and modifies its color accordingly
   * @param dt Delta time
   */
  void update(double dt);
};

#endif  // DRONE_COLOR_DECORATOR_H