// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation

#ifndef DRONE_DAMAGE_DECORATOR_H
#define DRONE_DAMAGE_DECORATOR_H

#include "Drone.h"
#include "DroneColorDecorator.h"
#include "DroneDecorator.h"
#include "Package.h"

/**
 * @class DroneDamageDecorator
 * @brief Decorator class that simulates damage effects on a drone.
 *
 * This decorator modifies the behavior of a drone by simulating damage
 * through altering its durability which affects its movement speed and
 * functionality within the simulation. It uses the Decorator design pattern to
 * extend the functionality of Drone at runtime without modifying the original
 * Drone class.
 */
class DroneDamageDecorator : public DroneDecorator {
 private:
  /// Factor for scaling the level of damage applied to the drone.
  double damageFactor;

  /// Accumulator for elapsed time since the last update.
  double timeAccumulator;

  /// Pointer to the original Drone being decorated.
  Drone* original_drone;

 public:
  /**
   * @brief Default Constructor that wraps a drone with damage behavior.
   * @param d Pointer to the Drone to be decorated.
   */
  DroneDamageDecorator(Drone* d);

  /**
   * @brief Updates the drone's state, applying damage effects over time.
   * @param dt Delta time since the last update.
   */
  void update(double dt);
};

#endif  // DRONE_DAMAGE_DECORATOR_H
