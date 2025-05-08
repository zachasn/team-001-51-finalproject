#include "ShippingQueue.h"

void ShippingQueue::addPackage(Package* package, NotificationSystem* notifier) {
  // Check for null package
  if (!package) {
    if (notifier) {
      notifier->publish("Error: Cannot add null package to queue");
    }
    return;
  }
  // Add package to list
  packages_.push_back(package);
  reorderQueue();
  // Notify addition
  if (notifier) {
    std::string message = "Package ";
    message = message + std::to_string(package->getId()) + " added to queue";
    notifier->publish(message);
  }
}

void ShippingQueue::removePackage(Package* package,
                                  NotificationSystem* notifier) {
  // Check for null package
  if (!package) {
    if (notifier) {
      notifier->publish("Error: Cannot remove null package from queue");
    }
    return;
  }
  // Look for package in list
  for (int i = 0; i < packages_.size(); i++) {
    if (packages_[i] == package) {
      packages_.erase(packages_.begin() + i);
      if (notifier) {
        std::string message = "Package ";
        message =
            message + std::to_string(package->getId()) + " removed from queue";
        notifier->publish(message);
      }
      return;
    }
  }
  // Notify if not found
  if (notifier) {
    notifier->publish("Error: Package not found in queue");
  }
}

void ShippingQueue::reorderQueue() {
  // Bubble sort for simplicity
  for (int i = 0; i < packages_.size(); i++) {
    for (int j = 0; j < packages_.size() - 1; j++) {
      bool swap = false;
      // Compare priorities
      if (packages_[j]->getPriorityLevel() <
          packages_[j + 1]->getPriorityLevel()) {
        swap = true;
      }
      // Compare order index for same priority
      else if (packages_[j]->getPriorityLevel() ==
               packages_[j + 1]->getPriorityLevel()) {
        if (packages_[j]->getOrderIndex() > packages_[j + 1]->getOrderIndex()) {
          swap = true;
        }
      }
      // Swap if needed
      if (swap) {
        Package* temp = packages_[j];
        packages_[j] = packages_[j + 1];
        packages_[j + 1] = temp;
      }
    }
  }
}

Package* ShippingQueue::getNextPackage() const {
  if (packages_.empty()) {
    return nullptr;
  }
  return packages_.front();
}