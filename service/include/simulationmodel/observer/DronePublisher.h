#ifndef DRONE_PUBLISHER_H_
#define DRONE_PUBLISHER_H_

#include <vector>

#include "DroneObserver.h"
#include "math/vector3.h"

class DroneObserver;

/**
 * @class DronePublisher
 * @brief Publisher for Drones to send location data
 *
 * This class follows the Observer design pattern
 */
class DronePublisher {
 public:
  /**
   * @brief Constructor for DronePublisher
   */
  DronePublisher() {}
  /**
  * @brief Destructor for DronePublisher
  */
  virtual ~DronePublisher() {};
  /**
   * @brief Adds an observer to publish data to
   * @param o DroneObserver to add
   */
  void addDroneObserver(DroneObserver* o) { reaper = o; }
  /**
   * @brief Removes the observer
   */
  void removeDroneObserver() { reaper = nullptr; }
  /**
   * @brief Retrives a pointer to the Drone Observer
   */
  DroneObserver* getReaper() { return reaper; }

  /**
   * @brief Method to publish location data
   * @param pos Drone's position as a vector
   */
  virtual void notifyDroneObserver(const Vector3& pos) = 0;

 private:
  DroneObserver* reaper = nullptr;
};

#endif
