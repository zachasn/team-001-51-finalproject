#ifndef SKY_REAPER_H_ 
#define SKY_REAPER_H_ 

#include "IEntity.h" 
#include "IStrategy.h" 
#include "math/vector3.h"
#include "Observer.h"
#include "Publisher.h"

class Package;

class SkyReaper : public Observer, public IEntity {
public:
    SkyReaper(const JsonObject& obj);
    ~SkyReaper();
    Package* interceptPackage();
    void update(double dt) override;
    bool available = false;
private:
    Package* package = nullptr;
    int radius;
    IStrategy* toDrone = nullptr;
};

#endif