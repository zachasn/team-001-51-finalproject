#ifndef DATA_MANAGER_
#define DATA_MANAGER_

#include "IEntity.h"
#include "SimulationModel.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// statistics for each drone
struct drone_stats {
  double distanceTraveled = 0.0; // distance traveled to delivery a package
  int packagesDelivered = 0; // number of packages delivered
  //double totalDistance = 0.0; // total distance traveled throughout simulation
  // int lostPackages = 0; // packages lost to adversary drones(not need right now)
  //bool condition = true; // true if damaged, false if not.(not need right now)
  std::vector<std::string> events; //
};

class DataManager {
  protected:
  DataManager() = default;
  std::map<int,drone_stats> data;

  public:
  DataManager(const DataManager&) = delete;
  static DataManager& getInstance() {
    static DataManager instance;
    return instance;
  }
  void distanceTraveled(int droneID, double distance) {
    data[droneID].distanceTraveled += distance;
  }

  void packageDelivered(int droneID) {
    data[droneID].packagesDelivered += 1;
    data[droneID].distanceTraveled = 0.0;
  }
  int getNumDelivery(int droneID) {
    return data[droneID].packagesDelivered;
  }
  drone_stats getStats(int droneID) {
    return data[droneID];
  }
  const std::map<int, drone_stats> getAllStats() {
    return data;
  }

  int exportData(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
      return 1;
    }

    file << "DroneID,DistanceTraveled,PackagesDelivered\n";

    for (const auto& row : data) {
      file << row.first << ","  << row.second.distanceTraveled << "," << row.second.packagesDelivered << "\n";
    }
    file.close();
    return 0;
  }

};
#endif
