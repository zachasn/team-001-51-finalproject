#ifndef ENTITY_DECORATOR_H_
#define ENTITY_DECORATOR_H_

#include <concepts>

#include "IEntity.h"

/**
 * @class IEntityDecorator
 * @brief Template base class for implementing decorators for entities derived
 * from IEntity.
 *
 * This class uses the Decorator design pattern to extend or modify the behavior
 * of an IEntity or any of its derived classes (e.g., Drone, Robot) without
 * modifying the original class. It delegates all method calls to the wrapped
 * entity and can be extended to override specific behavior.
 *
 * @tparam T The type of the entity being decorated, must be derived from
 * IEntity.
 */
template <std::derived_from<IEntity> T = IEntity>
class IEntityDecorator : public T {
 public:
  /**
   * @brief Constructs the decorator by wrapping the given entity.
   * @param e Pointer to the entity to be decorated.
   */
  IEntityDecorator(T* e) : T(e->getDetails()), sub(e) {}

  /**
   * @brief Virtual destructor that cleans up the wrapped entity.
   */
  virtual ~IEntityDecorator() {
    if (sub) delete sub;
  }
  /**
   * @brief Forwards linking to the simulation model to the wrapped entity.
   * @param model Pointer to the simulation model.
   */
  virtual void linkModel(SimulationModel* model) {
    return sub->linkModel(model);
  }

  /**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  virtual int getId() const { return sub->getId(); }

  /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  virtual Vector3 getPosition() const { return sub->getPosition(); }

  /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  virtual Vector3 getDirection() const { return sub->getDirection(); }

  /**
   * @brief Gets the details of the entity.
   * @return The details of the entity.
   */
  virtual const JsonObject& getDetails() const { return sub->getDetails(); }

  /**
   * @brief Gets the color of the entity
   * @return The color of the entity
   */
  virtual std::string getColor() const { return sub->getColor(); }

  /**
   * @brief Gets the name of the entity
   * @return The name of the entity
   */
  virtual std::string getName() const { return sub->getName(); }

  /**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  virtual double getSpeed() const { return sub->getSpeed(); }

  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  virtual void setPosition(Vector3 pos_) { return sub->setPosition(pos_); }

  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  virtual void setDirection(Vector3 dir_) { return sub->setDirection(dir_); }

  /**
   * @brief Sets the color of the entity
   * @param col_ The new color of the entity
   */
  virtual void setColor(std::string col_) { return sub->setColor(col_); }

  /**
   * @brief Rotate the entity around y axis.
   * @param angle The angle to rotate the entity by.
   */
  virtual void rotate(double angle) { return sub->rotate(angle); }

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   */
  virtual void update(double dt) { return sub->update(dt); }

  /**
   * @brief Adds an observer to the wrapped entity.
   *
   * Registers an observer that will be notified when the decorated entity
   * generates an event. This enables external components to react to changes
   * or actions taken by the entity.
   *
   * @param o Pointer to the observer to be added.
   */
  virtual void addObserver(const IObserver* o) { return sub->addObserver(o); };

  /**
   * @brief Removes an observer from the wrapped entity.
   *
   * Unregisters a previously added observer, so it will no longer receive
   * notifications from the entity.
   *
   * @param o Pointer to the observer to be removed.
   */
  virtual void removeObserver(const IObserver* o) {
    return sub->removeObserver(o);
  };

  /**
   * @brief Notifies all registered observers with a message.
   *
   * Broadcasts a message to all observers currently registered with the entity.
   * This is typically used to signal changes in state or behavior.
   *
   * @param message The notification message to send to observers.
   */
  virtual void notifyObservers(const std::string& message) {
    return sub->notifyObservers(message);
  };

 protected:
  /// Pointer to the entity being decorated.
  T* sub = nullptr;
};

#endif

// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation