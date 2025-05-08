#ifndef NOTIFICATION_SYSTEM_H_
#define NOTIFICATION_SYSTEM_H_

#include <iostream>
#include <string>

#include "IPublisher.h"
#include "util/json.h"

/**
 * @brief Simple notification system for console and UI messages.
 */
class NotificationSystem : public IPublisher {
 public:
  /**
   * @brief Publish a message to console.
   * @param message The message to show.
   */
  void publish(const std::string& message);

  /**
   * @brief Publish a message to the UI via observers.
   * @param message The message to show.
   */
  void publishToUI(const std::string& message);
};

#endif  // NOTIFICATION_SYSTEM_H_