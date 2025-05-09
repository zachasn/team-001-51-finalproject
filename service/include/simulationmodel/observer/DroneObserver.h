#ifndef DRONE_OBSERVER_H_
#define DRONE_OBSERVER_H_

#include <iostream>
#include <string>

#include "DronePublisher.h"
#include "IEntity.h"
#include "IObserver.h"
#include "math/vector3.h"

class DronePublisher;
class Drone;

/**
 * @brief Abstract observer class for receiving drone position updates.
 *
 * This class defines the interface for any component that wishes to observe
 * drone movements and receive notifications when a drone's position changes.
 *
 * Classes that inherit from DroneObserver must implement the notifyPosition
 * method.
 */
class DroneObserver {
 public:
  /**
   * @brief Default constructor.
   */
  DroneObserver() {}

  /**
   * @brief Virtual destructor.
   */
  virtual ~DroneObserver() {}

  /**
   * @brief Receives position updates from other drones.
   *
   * Called by a DronePublisher when a drone's position changes. Implementers
   * can use this to react to or track nearby drones.
   *
   * @param location The current position of the drone.
   * @param d Pointer to the drone sending the update.
   */
  virtual void notifyPosition(const Vector3& location, Drone* d) = 0;
};

#endif  // DRONE_OBSERVER_H_

// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation