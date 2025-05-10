#ifndef SKY_REAPER_H_
#define SKY_REAPER_H_

#include "DataManager.h"
#include "DroneObserver.h"
#include "DronePublisher.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;
class Drone;

class SkyReaper : public DroneObserver, public IEntity {
 public:
  /**
   * @brief Creates SkyReaper entity
   * @param obj JsonObject with entity details
   */
  SkyReaper(const JsonObject& obj);
  /**
   * @brief Deletes SkyReaper entity
   */
  ~SkyReaper();
  /**
   * @brief Attemps brute-force cracking to steal package
   */
  void interceptPackage();
  /**
   * @brief Updates SkyReaper position
   * @param dt - Delta Time
   */
  void update(double dt) override;
  /**
   * @brief SkyReaper receives position information from other drones
   * @param location Drone position as a vector
   * @param d Pointer to drone object
   */
  void notifyPosition(const Vector3& location, Drone* d) override;

 private:
    Drone* target = nullptr;
  Vector3 target_pos;
  double radius = 350.0;
  Package* package = nullptr;
  IStrategy* toDrone = nullptr;
};

#endif