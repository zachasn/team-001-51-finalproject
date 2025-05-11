#include "DataManager.h"

void DataManager::addEntity(int entityId, std::string entityName,
                            std::string entityType) {
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
}

void DataManager::distanceTraveled(int entityId) {
  data[entityId].distanceTraveled++;
}

void DataManager::packagesDelivered(int entityId) {
  data[entityId].packagesDelivered++;
}

void DataManager::lostPackages(int entityId) { data[entityId].lostPackages++; }

void DataManager::setCondition(int entityId, double durability) {
  if (durability >= 80) {
    data[entityId].condition = "Excellent";
  } else if (durability >= 40) {
    data[entityId].condition = "Good";
  } else if (durability >= 1) {
    data[entityId].condition = "Poor";
  } else {
    data[entityId].condition = "Broken";
  }
}

int DataManager::exportData() {
  std::ofstream file("simulation_data.csv");
  if (!file.is_open()) {
    return 1;
  }
  file << "Creation_time,Entity_type,Entity_id,Entity_name,Distance_traveled("
          "miles),Packages_delivered,Lost_packages,Condition\n";
  for (const auto& [entityId, stats] : data) {
    file << stats.creationTime << "," << stats.entityType << "," << entityId
         << "," << stats.entityName << "," << stats.distanceTraveled << ","
         << stats.packagesDelivered << "," << stats.lostPackages << ","
         << stats.condition << "\n";
  }
  file.close();
  return 0;
}