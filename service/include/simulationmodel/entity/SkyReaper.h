#ifndef SKY_REAPER_H_ 
#define SKY_REAPER_H_ 

#include "IEntity.h" 
#include "IStrategy.h" 
#include "math/vector3.h"
#include "Observer.h"
#include "Publisher.h"

class Package;
class Drone;

class SkyReaper : public Observer, public IEntity {
public:
    SkyReaper(const JsonObject& obj);
    ~SkyReaper();
    Package* interceptPackage();
    const Vector3* getTargetVec();
    void update(double dt) override;
    void notifyPosition(const Vector3& location, const Publisher* p) override;
private:
    Package* package = nullptr;
    IStrategy* toDrone = nullptr;
    int radius;
    const Vector3* target_pos = nullptr;
};

#endif