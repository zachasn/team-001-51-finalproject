#ifndef SHIPPING_QUEUE_H_
#define SHIPPING_QUEUE_H_

#include <vector>

#include "Package.h"
#include "NotificationSystem.h"

/**
 * @brief Manages a sorted queue of packages by priority with FIFO ordering.
 */
class ShippingQueue {
 public:
  /**
   * @brief Add a package to the queue and sort it.
   * @param package Pointer to the package.
   * @param notifier Pointer to NotificationSystem for updates.
   */
  void addPackage(Package* package, NotificationSystem* notifier);
  /**
   * @brief Remove a package from the queue.
   * @param package Pointer to the package to remove.
   * @param notifier Pointer to NotificationSystem for updates.
   */
  void removePackage(Package* package, NotificationSystem* notifier);

  /**
   * @brief Reorder the queue by priority (Expedited > Standard > No Rush) and
   * FIFO.
   */
  void reorderQueue();

  /**
   * @brief Get the highest-priority package.
   * @return Pointer to the package, or nullptr if empty.
   */
  Package* getNextPackage() const;

 private:
  std::vector<Package*> packages_;  // List of packages
};

#endif  // SHIPPING_QUEUE_H_