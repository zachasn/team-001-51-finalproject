#ifndef DATA_MANAGER_
#define DATA_MANAGER_

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "IEntity.h"
#include "SimulationModel.h"

//--------------------  Data Manager ----------------------------

/**
 * @brief A struct that contains the statistics of an entity
 *
 */
struct entity_stats {
  std::string entityName;
  std::string entityType;
  double distanceTraveled;  // distance traveled by the entity through out the
                            // simulation in miles
  int packagesDelivered;    // number of packages delivered by the entity
  int lostPackages;         // number of packages lost to an adversary drone
  std::string condition;  // the condition of the entity, can be "damaged"(when
                          // damaged by weather) or "operational"
  std::string creationTime;  // Time entity is created
};

/**
 * @brief This class is responsible for collecting and managing data from
 * entities
 */
class DataManager {
 protected:
  DataManager();
  std::map<int, entity_stats> data;

 public:
  static DataManager& getInstance() {
    static DataManager instance;
    return instance;
  }

  DataManager(const DataManager&) = delete;
  DataManager& operator=(const DataManager&) = delete;

  /**
   * @brief Add an entity to the data manager
   * @param entityId ID of the entity
   * @param entityName Name of the entity
   * @param entityType Type of entity
   */
  void addEntity(int entityId, std::string entityName, std::string entityType);

  /**
   * @brief Increment the distance traveled by an entity
   * @param entityId The ID of the entity
   */
  void distanceTraveled(int entityId);

  /**
   * @brief Increment the number of packages delivered by an entity
   * @param entityId The ID of the entity
   */
  void packagesDelivered(int entityId);

  /**
   * @brief Increment the number of lost packages by an entity
   * @param entityId The ID of the entity
   */
  void lostPackages(int entityId);

  /**
   * @brief Set the condition of an entity
   * @param entityId ID of the entity
   * @param durability durability of the entity
   */
  void setCondition(int entityId, double durability);

  /**
   * @brief Export the data to a CSV file
   * @return 0 on sucess, 1 on failure
   */
  int exportData();
};

#endif
