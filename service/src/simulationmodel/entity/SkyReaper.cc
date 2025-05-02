#include <cmath>

#include "SkyReaper.h" 
#include "BfsStrategy.h"
#include "BreadthFirstSearch.h"
#include "SimulationModel.h"
#include "Package.h"
#include "IEntity.h" 
#include "math/vector3.h"
#include "DronePublisher.h"

SkyReaper::SkyReaper(const JsonObject& obj) : IEntity(obj) { }

SkyReaper::~SkyReaper() {
    if (package) {
        delete package;
    }
}

Package* SkyReaper::interceptPackage() {
    return nullptr;
}

void SkyReaper::update(double dt) {
    if (target != nullptr) {
        toDrone->move(this, dt); 
        double diff = target_pos.dist(this->position);
        std::cout << "moving toward target... " << std::endl;
        if (diff < this->radius) {
            std::cout << "Sky Reaper intercept" << std::endl;
            std::string msg = "Sky Reaper intercepting drone...";
            notifyObservers(msg); 
            toDrone = nullptr;
        }
        if (toDrone->isCompleted()) {
            target = nullptr;
            std::cout << "Sky Reaper has reached the drone" << std::endl;
        }
    }
}

void SkyReaper::notifyPosition(const Vector3& location, const Drone* d) {
    //std::cout << "inside sky reaper positoin... " << std::endl;
    double dist = this->getPosition().dist(location);
    if (dist < this->radius) {
        std::cout << "Inside range" << std::endl;
    }
    if (!target) {
        //Package* p = const_cast<Drone*>(d)->getPackage();
        target = d;
        Vector3 target_position = d->getPosition(); 
        Package* p = const_cast<Drone*>(target)->getPackage();
        Vector3 package_dest = p->getDestination();
        //Vector3 temp = const_cast<Drone*>(d)->getPosition();
        setDirection(target_position);
        std::cout << target_position << std::endl;
        //std::cout << d->getDestination() << std::endl;
        toDrone = new BfsStrategy(position, target_position, model->getGraph());
    }
}
