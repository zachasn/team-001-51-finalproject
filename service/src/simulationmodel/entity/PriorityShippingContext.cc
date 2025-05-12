//AI citation: Used ChatGPT for logic improvements and debugging
#include "PriorityShippingContext.h"

PriorityShippingContext::PriorityShippingContext() {
  state_ = new StandardState();
}

PriorityShippingContext::~PriorityShippingContext() { delete state_; }

void PriorityShippingContext::setState(PriorityShippingState* new_state) {
  delete state_;
  state_ = new_state;
}

void PriorityShippingContext::changeState(int priority,
                                          NotificationSystem* notifier,
                                          const Package* package) {
  // Check if priority is valid
  if (priority < NO_RUSH || priority > EXPEDITED) {
    if (notifier) {
      notifier->publish("Error: Invalid priority value");
    }
    return;
  }
  // Check if state can change
  std::string error = state_->canChangeState(package);
  if (error != "") {
    if (notifier) {
      std::string message = error;
      if (package != nullptr) {
        message = message + " for package " + std::to_string(package->getId());
      }
      notifier->publish(message);
    }
    return;
  }
  // Save old state name
  std::string old_name = getName();
  // Change to new state
  if (priority == NO_RUSH) {
    setState(new NoRushState());
  } else if (priority == STANDARD) {
    setState(new StandardState());
  } else if (priority == EXPEDITED) {
    setState(new ExpeditedState());
  }
  // Notify change
  if (notifier) {
    std::string message =
        "Priority changed from " + old_name + " to " + getName();
    notifier->publish(message);
  }
}

int PriorityShippingContext::getPriorityLevel() const {
  return state_->getPriorityLevel();
}

std::string PriorityShippingContext::getName() const {
  return state_->getName();
}