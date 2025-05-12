//AI citation: ChatGPT was used for the doxygen comments and input on whether the attributes are sufficient or not
#ifndef TRIP_SCHEDULER_H_
#define TRIP_SCHEDULER_H_

#include <vector>

#include "NotificationSystem.h"
#include "Package.h"
#include "Robot.h"
#include "ShippingQueue.h"

/**
 * @brief Schedules trips for robots to deliver packages.
 */
class TripScheduler {
 public:
  /**
   * @brief Constructor with notification system.
   * @param notifier Pointer to NotificationSystem for updates.
   */
  TripScheduler(NotificationSystem* notifier);

  /**
   * @brief Assign packages to available robots using priority queue.
   * @param robots Vector of available robots.
   * @param queue ShippingQueue containing packages.
   */
  void assignPackages(std::vector<Robot*>& robots, ShippingQueue& queue);

 private:
  NotificationSystem* notifier_;  // For sending updates
};

#endif  // TRIP_SCHEDULER_H_