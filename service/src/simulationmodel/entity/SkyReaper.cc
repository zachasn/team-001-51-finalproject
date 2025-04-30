#include <cmath>

#include "SkyReaper.h" 
#include "BeelineStrategy.h"
#include "SimulationModel.h"
#include "Package.h"
#include "IEntity.h" 
#include "math/vector3.h"
#include "Publisher.h"

SkyReaper::SkyReaper(const JsonObject& obj) : IEntity(obj) { }

SkyReaper::~SkyReaper() {
    if (package) {
        delete package;
    }
}

Package* SkyReaper::interceptPackage() {
    return nullptr;
}

const Vector3* SkyReaper::getTargetVec() {
    const Vector3* temp = target_pos;
    return temp;
}

void SkyReaper::update(double dt) {
    if (target_pos) {
        toDrone->move(this, dt); 
        Vector3 temp = *const_cast<Vector3*>(target_pos);
        toDrone = new BeelineStrategy(this->position, temp);
        double diff = getTargetVec()->dist(this->position);
        std::cout << diff << std::endl;
        if (diff < 10) {
            std::string msg = "Sky Reaper intercepting drone...";
            notifyObservers(msg); 
            toDrone = nullptr;
        }
    }
}

void SkyReaper::notifyPosition(const Vector3& location, const Publisher* p) {
    std::cout << "inside sky reaper positoin... " << std::endl;
    double dist = getPosition().dist(location);
    //std::cout << dist << std::endl;

    target_pos = &location;
    setDirection(location);
    Vector3 temp = *const_cast<Vector3*>(target_pos);
    toDrone = new BeelineStrategy(position, temp);
}
