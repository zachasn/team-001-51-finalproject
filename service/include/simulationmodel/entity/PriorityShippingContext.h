#ifndef PRIORITY_SHIPPING_CONTEXT_H_
#define PRIORITY_SHIPPING_CONTEXT_H_

#include <string>

#include "Package.h"
#include "PriorityShippingState.h"
#include "util/NotificationSystem.h"

/**
 * @brief Manages priority state transitions for a Package.
 */
class PriorityShippingContext {
 public:
  /**
   * @brief Constructor initializes with Standard state.
   */
  PriorityShippingContext();

  /**
   * @brief Destructor to clean up state.
   */
  ~PriorityShippingContext();

  /**
   * @brief Set a new priority state.
   * @param new_state Pointer to the new state.
   */
  void setState(PriorityShippingState* new_state);

  /**
   * @brief Change the priority based on int value.
   * @param priority The new priority (NO_RUSH, STANDARD, EXPEDITED).
   * @param notifier Pointer to NotificationSystem for updates.
   * @param package Pointer to Package to check state.
   */
  void changeState(int priority, NotificationSystem* notifier,
                   const Package* package);

  /**
   * @brief Get the current priority level.
   * @return Integer priority level.
   */
  int getPriorityLevel() const;

  /**
   * @brief Get the name of the current priority.
   * @return String name of the priority.
   */
  std::string getName() const;

 private:
  PriorityShippingState* state_;  // Current state
};

#endif  // PRIORITY_SHIPPING_CONTEXT_H_
