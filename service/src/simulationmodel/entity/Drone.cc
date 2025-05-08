#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DataManager.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "DroneObserver.h"
#include "DronePublisher.h"
#include "Package.h"
#include "SimulationModel.h"

Drone::Drone(const JsonObject& obj) : IEntity(obj) {
  available = true;
  this->lastPosition = this->position;
  durability = 100;
  weather = WeatherControl::GetInstance();
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  addDroneObserver(model->getAdversary());
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      std::string message = getName() + " heading to: " + package->getName();
      notifyObservers(message);
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new AstarStrategy(
            packagePosition, finalDestination, model->getGraph());
      } else if (strat == "dfs") {
        toFinalDestination = new DfsStrategy(packagePosition, finalDestination,
                                             model->getGraph());
      } else if (strat == "bfs") {
        toFinalDestination = new BfsStrategy(packagePosition, finalDestination,
                                             model->getGraph());
      } else if (strat == "dijkstra") {
        toFinalDestination = new DijkstraStrategy(
            packagePosition, finalDestination, model->getGraph());
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

double Drone::getDurability() {
  return durability;
}

void Drone::updateDurability(double damage) {
  durability -= damage;
  DataManager::getInstance().setCondition(id, durability);
  if (durability <= 0) {
    notifyObservers(name + " has broken and been removed from the simulation.");
    model->scheduledDeliveries.push_back(package);
    model->removeEntity(id);
  }
}

void Drone::updateSpeedBasedOnDurability() {
  // speed decreases linearly down to a minumum of half its original speed before drone breaks
  speed = 30.0 * (0.5 + (durability / 100.0) * 0.5);
}

void Drone::applyWind(double dt) {
  Vector3 scaledWind = weather->getWind() * (dt / 10);
  position = position + scaledWind;
}

void Drone::update(double dt) {

  Vector3 currenPosition = getPosition();

  applyWind(dt);

  if (available) getNextDelivery();

  if (toPackage) {
    toPackage->move(this, dt);

    if (toPackage->isCompleted()) {
      std::string message = getName() + " picked up: " + package->getName();
      notifyObservers(message);
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    notifyDroneObserver(position);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);

      notifyDroneObserver(position);
    }

    if (toFinalDestination->isCompleted()) {
      std::string message = getName() + " dropped off: " + package->getName();
      notifyObservers(message);
      DataManager::getInstance().packagesDelivered(id);
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }

  double diff = this->lastPosition.dist(this->position);
  this->distanceTraveled += diff;
  this->lastPosition = this->position;
  if (this->distanceTraveled > 1625.0) {
    DataManager::getInstance().distanceTraveled(id);
    this->distanceTraveled = 0;
  }

  // enforce map boundaries
  if (position.x < -1470) position.x = -1470;
  if (position.x > 1570) position.x = 1570;

  if (position.z < -880) position.z = -880;
  if (position.z > 880) position.z = 880;

}
Package* Drone::getPackage() const { return package; };

void Drone::takePackage() {
  package = nullptr;
  toFinalDestination = nullptr;
  available = true;
  pickedUp = false;
}

void Drone::notifyDroneObserver(const Vector3& pos) {
  this->getReaper()->notifyPosition(pos, this);
}