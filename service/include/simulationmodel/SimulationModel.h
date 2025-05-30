// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation

#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include <deque>
#include <map>
#include <set>

#include "CompositeFactory.h"
#include "Drone.h"
#include "DroneObserver.h"
#include "Graph.h"
#include "IController.h"
#include "IEntity.h"
#include "IObserver.h"
#include "NotificationSystem.h"
#include "Robot.h"
#include "ShippingQueue.h"
#include "TripScheduler.h"
#include "WeatherControl.h"

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. It can
 * communicate with the controller, manage entities, schedule trips, and handle
 * weather, adversaries, and delivery logic.
 */
class SimulationModel : public IObserver {
 public:
  /**
   * @brief Constructor that creates a SimulationModel instance.
   * @param controller Reference to the controller used for communication.
   * @param notifier Pointer to the system used for delivering notifications.
   */
  SimulationModel(IController& controller, NotificationSystem* notifier);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type Graph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::Graph* graph);

  /**
   * @brief Creates a new simulation entity with priority support.
   * @param entity JSON object with entity data.
   * @return Pointer to created entity, or nullptr if invalid.
   */
  IEntity* createEntity(const JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   *
   * @param id of the entity to be removed
   */
  void removeEntity(int id);

  /**
   * @brief Schedule a trip with priority queue.
   * @param details JSON object with trip details.
   */
  void scheduleTrip(const JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns Graph* graph pointer
   */
  const routing::Graph* getGraph() const;

  /**
   * @brief Receives and processes external notification messages.
   * @param message String message received from another component.
   */
  void notify(const std::string& message) const;

  /**
   * @brief Get the adversarial drone observer (e.g., SkyReaper).
   * @return Pointer to the adversary observer, or nullptr if none.
   */
  DroneObserver* getAdversary();

  /**
   * @brief Get the currently selected encryption type.
   * @return Encryption type as a string.
   */
  std::string getEncryption();

  /// A queue of packages that have been scheduled for delivery.
  std::deque<Package*> scheduledDeliveries;

 protected:
  /// Reference to the simulation controller.
  IController& controller;

  /// Weather control system for simulating environmental effects.
  WeatherControl* weather;

  /// Map of all active simulation entities, keyed by ID.
  std::map<int, IEntity*> entities;

  /// Set of entity IDs marked for removal.
  std::set<int> removed;

  /**
   * @brief Helper function to remove an entity from the simulation.
   * @param id ID of the entity to remove.
   */
  void removeFromSim(int id);

  /// Pointer to the routing graph used for pathfinding.
  const routing::Graph* graph = nullptr;

  /// Factory used to create various types of entities.
  CompositeFactory entityFactory;

  /// Pointer to the adversarial SkyReaper drone.
  DroneObserver* adversary = nullptr;

  /// The type of encryption used for adversary detection/communication.
  std::string encryptionType;

  /// Trip scheduling system for assigning delivery tasks.
  TripScheduler* scheduler_;

  /// Priority-aware shipping queue used for managing deliveries.
  ShippingQueue* queue_;

  /// Notification system used for sending messages to observers.
  NotificationSystem* notifier_;
};

#endif  // SIMULATION_MODEL_H_
