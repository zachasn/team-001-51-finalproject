#ifndef Helicopter_H_
#define Helicopter_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class Helicopter
 * @brief Represents a helicopter entity in the simulation.
 *
 * The Helicopter class models an autonomous helicopter that follows a movement
 * strategy. It keeps track of the distance traveled and reports travel
 * milestones.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopter are created with a name
   * @param obj JSON object containing the drone's information
   */
  Helicopter(const JsonObject& obj);

  /**
   * @brief Destructor for the Helicopter.
   *
   * Cleans up dynamically allocated resources such as the movement strategy.
   */
  ~Helicopter();

  /**
   * @brief Updates the helicopter's position based on its movement strategy.
   *
   * Called every simulation step with a delta time. Tracks distance traveled.
   *
   * @param dt Delta time in seconds since the last update.
   */
  void update(double dt);

 private:
  /// Current movement strategy for the helicopter.
  IStrategy* movement = nullptr;

  /// Total distance traveled since creation or last reset.
  double distanceTraveled = 0;

  /// Counter for number of "miles" traveled milestones.
  unsigned int mileCounter = 0;

  /// Position from the last update, used to calculate incremental distance.
  Vector3 lastPosition;
};

#endif

// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation