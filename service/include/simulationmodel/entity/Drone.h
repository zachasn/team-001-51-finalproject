// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation

#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "DataManager.h"
#include "DroneObserver.h"
#include "DronePublisher.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "WeatherControl.h"
#include "math/vector3.h"

class Package;

/**
 * @class Drone
 * @brief Represents a drone in a physical delivery system.
 *
 * Drones move using Euler integration based on velocity and direction. They can
 * pick up and deliver packages, respond to weather effects (wind), track
 * durability, and interact with scheduling and observer systems.
 */
class Drone : public IEntity, public DronePublisher {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(const JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Returns package it has assigned
   */
  Package* getPackage() const;

  /**
   * @brief Returns the drones current durability level
   */
  double getDurability();

  /**
   * @brief updates the drones current durability level
   * @param damage the amount of damage to inflict on current drone durability
   */
  void updateDurability(double damage);

  /**
   * @brief updates the drones movement speed based on its current durability
   */
  void updateSpeedBasedOnDurability();

  /**
   * @brief applies the effect of the wind disturbance to the drones position
   * @param dt Delta time
   */
  void applyWind(double dt);

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Notifies the reaper of the drone's current position.
   * @param pos The new position of the drone.
   */
  void notifyDroneObserver(const Vector3& pos) override;

  /**
   * @brief Has the reaper take the package and resets the drones availability
   */
  void takePackage();

  /// Indicates whether the drone is available to accept a new delivery.
  bool available = false;

  /// Indicates whether the current package has been picked up.
  bool pickedUp = false;

 private:
  /// Current durability level of the drone.
  double durability;

  /// Pointer to the assigned package.
  Package* package = nullptr;

  /// Strategy used to move toward the package.
  IStrategy* toPackage = nullptr;

  /// Strategy used to move toward the final delivery destination.
  IStrategy* toFinalDestination = nullptr;

  /// Distance traveled while delivering the current package.
  double distanceTraveled = 0;

  /// Last recorded position used for tracking movement distance.
  Vector3 lastPosition;

  /// Pointer to the weather control system for applying wind effects.
  WeatherControl* weather;
};

#endif
