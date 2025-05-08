#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "simulationmodel/entity/PriorityShippingContext.h"
#include "simulationmodel/util/NotificationSystem.h"
#include "util/json.h"

class Robot;
class SimulationModel;
/**
 * @brief Represents a package in the drone simulation with priority state
 * support.
 */
class Package : public IEntity {
 public:
  /**
   * @brief Constructor initializing package with JSON data and Standard
   * priority.
   * @param obj JSON object containing the package's information.
   */
  Package(const JsonObject& obj);

  /**
   * @brief Destructor to clean up priority context.
   */
  virtual ~Package() { delete priority_context_; }

  /**
   * @brief Link this package to the simulation model.
   * @param model Pointer to the SimulationModel.
   */
  virtual void linkModel(
      SimulationModel* model) {  // CHANGE: ADDED TO MATCH IEntity
    this->model = model;
  }

  /**
   * @brief Gets the Package's destination.
   * @return The Package's destination.
   */
  virtual Vector3 getDestination() const;

  /**
   * @brief Returns the name of the strategy for this package.
   * @return String name of strategy.
   */
  virtual std::string getStrategyName() const;

  /**
   * @brief Returns the owner of the package.
   * @return Pointer to Robot owning the package.
   */
  virtual Robot* getOwner() const;

  /**
   * @brief Returns whether or not the package needs to be delivered.
   * @return Boolean value of the above statement.
   */
  virtual bool requiresDelivery() const;

  /**
   * @brief Set the Strategy Name.
   * @param strategyName_ Strategy name.
   */
  virtual void setStrategyName(std::string strategyName_);

  /**
   * @brief Updates the Package.
   * @param dt Difference in time since last update.
   */
  virtual void update(double dt);

  /**
   * @brief Sets the attributes for delivery.
   * @param owner Robot for the package to be delivered to.
   */
  virtual void initDelivery(Robot* owner);

  /**
   * @brief Gives the robot/owner this package.
   */
  virtual void handOff();

  /**
   * @brief Set a new priority if allowed.
   * @param priority The new priority (NO_RUSH = 0, STANDARD = 1, EXPEDITED =
   * 2).
   * @param notifier Pointer to NotificationSystem for updates.
   * @return True if priority was changed, false if not allowed.
   */
  virtual bool setPriority(int priority, NotificationSystem* notifier) {
    // Check if package is not picked up or delivered
    if (!is_picked_up_ && !is_delivered_) {
      priority_context_->changeState(
          priority, notifier, this);  // CHANGE: ADDED this FOR changeState
      return true;
    }
    // Notify error if notifier exists
    if (notifier) {
      std::string message = "Error: Cannot change priority for package ";
      message = message + std::to_string(getId()) + " after pickup or delivery";
      notifier->publish(message);
    }
    return false;  // CHANGE: MOVED RETURN OUTSIDE if
  }

  /**
   * @brief Mark package as picked up by a drone.
   */
  virtual void onPickup() { is_picked_up_ = true; }

  /**
   * @brief Mark package as delivered.
   */
  virtual void onDelivery() { is_delivered_ = true; }

  /**
   * @brief Get the current priority level.
   * @return Integer priority level (0 for No Rush, 1 for Standard, 2 for
   * Expedited).
   */
  virtual int getPriorityLevel() const {
    return priority_context_->getPriorityLevel();
  }

  /**
   * @brief Get the current priority name.
   * @return String name (e.g., "Expedited").
   */
  virtual std::string getPriorityName() const {
    return priority_context_->getName();
  }

  /**
   * @brief Get the order index for FIFO sorting.
   * @return Integer index.
   */
  virtual int getOrderIndex() const { return order_index_; }

  /**
   * @brief Check if package is picked up.
   * @return True if picked up, false otherwise.
   */
  virtual bool isPickedUp() const {  // CHANGE: ADDED FOR canChangeState
    return is_picked_up_;
  }

  /**
   * @brief Check if package is delivered.
   * @return True if delivered, false otherwise.
   */
  virtual bool isDelivered() const {  // CHANGE: ADDED FOR canChangeState
    return is_delivered_;
  }

 protected:
  bool requiresDelivery_ = true;
  Vector3 destination;
  std::string strategyName;
  Robot* owner = nullptr;
  PriorityShippingContext* priority_context_;  // Priority state management
  bool is_picked_up_ = false;                  // True if picked up
  bool is_delivered_ = false;                  // True if delivered
  int order_index_;                            // For FIFO sorting
  static int next_index_;                      // Tracks next index
};

// Static member initialization
int Package::next_index_ = 0;

#endif  // PACKAGE_H
