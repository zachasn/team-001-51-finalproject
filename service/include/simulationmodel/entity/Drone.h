#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "DroneObserver.h"
#include "DronePublisher.h"
#include "IEntity.h"
#include "IStrategy.h"

class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
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

  void notifyDroneObserver(const Vector3& pos) override;

  void takePackage();

  bool available = false;
  bool pickedUp = false;

 private:
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
  // to calculate distance traveled by drone when its delivering a package
  double distanceTraveled = 0;
  Vector3 lastPosition;
};

#endif
