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
   * @param entityType The type of entity
   */
  void addEntity(int entityId, std::string entityName, std::string entityType) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%b %d %Y %H:%M");
    data[entityId].creationTime = ss.str();
    data[entityId].entityName = entityName;
    data[entityId].entityType = entityType;
    data[entityId].distanceTraveled = 0;
    data[entityId].packagesDelivered = 0;
    data[entityId].lostPackages = 0;
    data[entityId].condition = "operational";
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
  void setCondition(int entityId, int condition) {
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
    file << "Creation_time, "
            "Entity_type,Entity_id,Entity_name,Distance_traveled(miles),"
            "Packages_delivered,Lost_"
            "packages,Condition\n";
    for (const auto& [entityId, stats] : data) {
      file << stats.creationTime << "," << stats.entityType << "," << entityId
           << "," << stats.entityName << "," << stats.distanceTraveled << ","
           << stats.packagesDelivered << "," << stats.lostPackages << ","
           << stats.condition << "\n";
    }
    file.close();
    return 0;
  }
};

#endif
