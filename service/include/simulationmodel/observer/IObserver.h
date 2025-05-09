#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>

/**
 * @brief Interface for generic observers that receive string-based
 * notifications.
 *
 * IObserver defines a basic observer interface used in the Observer design
 * pattern. Classes implementing this interface can receive arbitrary
 * string-based messages from a subject (or publisher).
 */
class IObserver {
 public:
  /**
   * @brief Receive a notification message.
   *
   * This method is called by the subject to send a textual update to the
   * observer.
   *
   * @param message A string message containing update information.
   */
  virtual void notify(const std::string &message) const = 0;
};

#endif  // IOBSERVER_H_

// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation