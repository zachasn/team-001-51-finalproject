#ifndef SKY_REAPER_H_ 
#define SKY_REAPER_H_ 

#include "IEntity.h" 
#include "IStrategy.h" 
#include "math/vector3.h"
#include "DroneObserver.h"
#include "DronePublisher.h"

class Package;
class Drone;

class SkyReaper : public DroneObserver, public IEntity {
public:
    SkyReaper(const JsonObject& obj);
    ~SkyReaper();
    Package* interceptPackage();
    void update(double dt) override;
    void notifyPosition(const Vector3& location, const Drone* d) override;
    const Drone* target = nullptr;
    Vector3 target_pos;
    double radius = 50.0;
private:
    Package* package = nullptr;
    IStrategy* toDrone = nullptr;
};

#endif