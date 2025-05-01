#ifndef DATA_MANAGER_
#define DATA_MANAGER_

#include <fstream>
#include <iostream>
#include <map>
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
  double distanceTraveled;  // distance traveled by the entity through out the
                            // simulation in miles
  int packagesDelivered;    // number of packages delivered by the entity
  int lostPackages;         // number of packages lost to an adversary drone
  std::string condition;  // the condition of the entity, can be "damaged"(when
                          // damaged by weather) or "operational"
};

/**
 * @brief This class is responsible for collecting, managing, and logging key
 * system data.
 */
class DataManager {
 protected:
  DataManager() = default;
  std::map<int, entity_stats> data;

 public:
  static DataManager& getInstance() {
    static DataManager instance;
    return instance;
  }
  /**
   * @brief Delete copy constructor and assignment operator to prevent multiple
   * instances
   */
  DataManager(const DataManager&) = delete;
  DataManager& operator=(const DataManager&) = delete;

  /**
   * @brief Add an entity to the data manager
   * @param entityId The ID of the entity
   * @param entityName The name of the entity
   */
  void addEntity(int entityId, std::string entityName) {
    data[entityId].entityName = entityName;
  }

  /**
   * @brief Increment the distance traveled by an entity
   * @param entityId The ID of the entity
   */
  void distanceTraveled(int entityId) { data[entityId].distanceTraveled++; }

  /**
   * @brief Increment the number of packages delivered by an entity
   * @param entityId The ID of the entity
   */
  void packagesDelivered(int entityId) { data[entityId].packagesDelivered++; }

  /**
   * @brief Increment the number of lost packages by an entity
   * @param entityId The ID of the entity
   */
  void lostPackages(int entityId) { data[entityId].lostPackages++; }

  /**
   * @brief Set the condition of an entity
   * @param entityId The ID of the entity
   * @param condition The condition of the entity
   */
  void condition(int entityId, int condition) {
    if (condition == 0) {
      data[entityId].condition = "operational";
    } else {
      data[entityId].condition = "damaged";
    }
  }

  /**
   * @brief Export the data to a CSV file
   * @return 0 on sucess, 1 on failure
   */
  int exportData() {
    std::ofstream file("simulation_data.csv");
    if (!file.is_open()) {
      return 1;
    }
    file << "Entity_id,Entity_name,Distance_traveled,Packages_delivered,Lost_"
            "packages,Condition\n";
    for (const auto& [entityId, stats] : data) {
      file << entityId << "," << stats.entityName << ","
           << stats.distanceTraveled << "," << stats.packagesDelivered << ","
           << stats.lostPackages << "," << stats.condition << "\n";
    }
    file.close();
    return 0;
  }
};

#endif
