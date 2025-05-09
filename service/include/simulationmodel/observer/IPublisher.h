// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation

#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

/**
 * @brief Interface for a publisher in the Observer pattern.
 *
 * IPublisher manages a set of observers and provides methods to add, remove,
 * and notify them of updates via string messages.
 */
class IPublisher {
 public:
  /**
   * @brief Add an observer to the notification list.
   *
   * Registers an observer to receive future notifications from this publisher.
   *
   * @param o Pointer to the observer to add.
   */
  virtual void addObserver(const IObserver* o);

  /**
   * @brief Remove an observer from the notification list.
   *
   * Unregisters an observer so it no longer receives notifications.
   *
   * @param o Pointer to the observer to remove.
   */
  virtual void removeObserver(const IObserver* o);

  /**
   * @brief Notify all registered observers with a message.
   *
   * Sends the provided message to each observer currently registered.
   *
   * @param message The notification message to broadcast.
   */
  virtual void notifyObservers(const std::string& message);

 private:
  /// A set of pointers to the registered observers.
  std::set<const IObserver*> observers;
};

#endif  // IPUBLISHER_H_
