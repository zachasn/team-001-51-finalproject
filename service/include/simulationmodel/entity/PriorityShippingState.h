#ifndef PRIORITY_SHIPPING_STATE_H_
#define PRIORITY_SHIPPING_STATE_H_

#include <string>
class Package;

// Priority levels
const int NO_RUSH = 0;    // Lowest
const int STANDARD = 1;   // Medium
const int EXPEDITED = 2;  // Highest

/**
 * @brief Base class for priority states.
 */
class PriorityShippingState {
 public:
  virtual ~PriorityShippingState() = default;
  /**
   * @brief Get the priority level (0 for No Rush, 1 for Standard, 2 for
   * Expedited).
   * @return Integer representing priority level.
   */
  virtual int getPriorityLevel() const = 0;
  /**
   * @brief Check if the priority can be changed.
   * @param package Pointer to the Package to check its state.
   * @return Empty string if allowed, error message if not.
   */
  virtual std::string canChangeState(const Package* package) const = 0;
  /**
   * @brief Get the name of the priority state.
   * @return String name (e.g., "No Rush").
   */
  virtual std::string getName() const = 0;
};

/**
 * @brief State for No Rush priority.
 */
class NoRushState : public PriorityShippingState {
 public:
  int getPriorityLevel() const;
  std::string canChangeState(const Package* package) const;
  std::string getName() const;
};

/**
 * @brief State for Standard priority.
 */
class StandardState : public PriorityShippingState {
 public:
  int getPriorityLevel() const;
  std::string canChangeState(const Package* package) const;
  std::string getName() const;
};

/**
 * @brief State for Expedited priority.
 */
class ExpeditedState : public PriorityShippingState {
 public:
  int getPriorityLevel() const;
  std::string canChangeState(const Package* package) const;
  std::string getName() const;
};

#endif  // PRIORITY_SHIPPING_STATE_H_