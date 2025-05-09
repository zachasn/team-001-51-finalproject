#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "DataManager.h"

/**
 * @class Human
 * @brief Represents a human entity in the simulation.
 *
 * Humans can move through the simulation using an assigned strategy. They can
 * track their distance traveled and whether they have reached a specific destination,
 * such as Keller Hall.
 */
class Human : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(const JsonObject& obj);

    /**
   * @brief Destructor for the Human entity.
   *
   * Frees any dynamically allocated resources such as the movement strategy.
   */
  ~Human();

    /**
   * @brief Updates the human's position and state.
   *
   * Called every simulation step with the time elapsed. Applies the current
   * movement strategy and tracks total distance traveled. Also checks if the
   * human has reached Keller Hall.
   *
   * @param dt Delta time in seconds since the last update.
   */
  void update(double dt);

 private:
  /// Static reference position representing Keller Hall in the simulation.
  static Vector3 kellerPosition;

  /// Current movement strategy assigned to the human.
  IStrategy* movement = nullptr;

  /// Indicates whether the human has reached Keller Hall.
  bool atKeller = false;

  /// Total distance traveled since simulation start.
  double distanceTraveled = 0;

  /// Position from the previous update, used for distance tracking.
  Vector3 lastPosition;
};

#endif
