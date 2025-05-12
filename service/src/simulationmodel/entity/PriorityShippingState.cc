//AI citation: Used ChatGPT for logic improvements and debugging
#include "PriorityShippingState.h"

#include "Package.h"

int NoRushState::getPriorityLevel() const { return NO_RUSH; }

std::string NoRushState::canChangeState(const Package* package) const {
  if (package == nullptr) {
    return "Error: No package provided";
  }
  if (package->isPickedUp() || package->isDelivered()) {
    return "Error: Package already picked up or delivered";
  }
  return "";
}

std::string NoRushState::getName() const { return "No Rush"; }

int StandardState::getPriorityLevel() const { return STANDARD; }

std::string StandardState::canChangeState(const Package* package) const {
  if (package == nullptr) {
    return "Error: No package provided";
  }
  if (package->isPickedUp() || package->isDelivered()) {
    return "Error: Package already picked up or delivered";
  }
  return "";
}

std::string StandardState::getName() const { return "Standard"; }

int ExpeditedState::getPriorityLevel() const { return EXPEDITED; }

std::string ExpeditedState::canChangeState(const Package* package) const {
  if (package == nullptr) {
    return "Error: No package provided";
  }
  if (package->isPickedUp() || package->isDelivered()) {
    return "Error: Package already picked up or delivered";
  }
  return "";
}

std::string ExpeditedState::getName() const { return "Expedited"; }