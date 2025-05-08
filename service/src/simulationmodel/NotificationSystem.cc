#include "NotificationSystem.h"

#include <iostream>

void NotificationSystem::publish(const std::string& message) {
  std::cout << "Notification: " << message << std::endl;
}

void NotificationSystem::publishToUI(const std::string& message) {
  notifyObservers(message);
}