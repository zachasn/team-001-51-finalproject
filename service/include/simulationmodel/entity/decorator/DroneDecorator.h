// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation

#ifndef DRONE_DECORATOR_H_
#define DRONE_DECORATOR_H_

#include "Drone.h"
#include "IEntityDecorator.h"
#include "Robot.h"

/**
 * @class DroneDecorator
 * @brief Abstract base class for drone decorators using the Decorator design
 * pattern.
 *
 * This class extends the functionality of a Drone by wrapping it and forwarding
 * method calls to the underlying Drone instance. Subclasses can override
 * specific behaviors to add new functionality without modifying the original
 * Drone class.
 */
class DroneDecorator : public IEntityDecorator<Drone> {
 public:
  /**
   * @brief Constructs a DroneDecorator that wraps a Drone instance.
   * @param d Pointer to the Drone to be decorated.
   */
  DroneDecorator(Drone* d) : IEntityDecorator(d) {}
  /**
   * @brief Forwards the call to retrieve the next delivery to the underlying
   * Drone.
   */
  virtual void getNextDelivery() { return sub->getNextDelivery(); };
  /**
   * @brief Forwards the call to get the current package to the underlying
   * Drone.
   * @return Pointer to the Package currently carried by the drone.
   */
  virtual Package* getPackage() { return sub->getPackage(); };
  /**
   * @brief Returns the underlying Drone object.
   * @return Pointer to the decorated Drone.
   */
  virtual Drone* getSub() { return sub; };
};

#endif
