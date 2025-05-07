#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "Package.h"
#include "SimulationModel.h"


Drone::Drone(const JsonObject& obj) : IEntity(obj) { 
  available = true; 
  durability = 100;
  weather = WeatherControl::GetInstance();
}

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
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

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      std::string message = getName() + " dropped off: " + package->getName();
      notifyObservers(message);
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }

  // enforce map boundaries
  if (position.x < -1470) position.x = -1470;
  if (position.x > 1570) position.x = 1570;

  if (position.z < -880) position.z = -880;
  if (position.z > 880) position.z = 880;

}
Package* Drone::getPackage() { return package; };
