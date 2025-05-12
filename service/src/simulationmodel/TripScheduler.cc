//AI citation: Used chatGPT for debugging and logic improvement for functions
#include "TripScheduler.h"

TripScheduler::TripScheduler(NotificationSystem* notifier) {
  notifier_ = notifier;
}

void TripScheduler::assignPackages(std::vector<Robot*>& robots,
                                   ShippingQueue& queue) {
  // Loop through robots
  for (int i = 0; i < robots.size(); i++) {
    // Check if robot is available
    if (robots[i] == nullptr || !robots[i]->requestedDelivery) {
      continue;  // Skip unavailable robots
    }
    // Get next package from queue
    Package* package = queue.getNextPackage();
    if (package == nullptr) {
      continue;  // No packages left
    }
    // Check if package needs delivery
    if (!package->requiresDelivery()) {
      queue.removePackage(package, notifier_);
      continue;  // Skip delivered packages
    }
    // Assign package to robot
    package->initDelivery(robots[i]);
    // Notify assignment
    if (notifier_) {
      std::string message = "Package ";
      message =
          message + std::to_string(package->getId()) + " assigned to robot";
      notifier_->publish(message);
      notifier_->publishToUI("Package " + std::to_string(package->getId()) +
                             " assigned to robot");
    }
    // Remove package from queue
    queue.removePackage(package, notifier_);
  }
}