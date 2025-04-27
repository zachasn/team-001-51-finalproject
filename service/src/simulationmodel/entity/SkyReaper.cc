#include <cmath>

#include "SkyReaper.h" 
#include "IStrategy.h"
#include "SimulationModel.h"
#include "Package.h"
#include "IEntity.h" 

SkyReaper::SkyReaper(const JsonObject& obj) : IEntity(obj) { available = true; }

SkyReaper::~SkyReaper() {
    if (package) {
        delete package;
    }
}

Package* SkyReaper::interceptPackage() {
    return nullptr;
}

void SkyReaper::update(double dt) {
    if (!available) {
        toDrone->move(this, dt); 
        if (toDrone->isCompleted()) {
            std::string msg = "Sky Reaper intercepting drone...";
            notifyObservers(msg); 
            delete toDrone;
            toDrone = nullptr;
        }
    }
}
