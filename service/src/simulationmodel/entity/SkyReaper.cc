#include "SkyReaper.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "BfsStrategy.h"
#include "BreadthFirstSearch.h"
#include "DataManager.h"
#include "DronePublisher.h"
#include "IEntity.h"
#include "Package.h"
#include "PackageEncryptionDecorator.h"
#include "SimulationModel.h"
#include "math/vector3.h"
#include "util/json.h"

class PackageEncryptionDecorator;

SkyReaper::SkyReaper(const JsonObject& obj) : IEntity(obj) {}

SkyReaper::~SkyReaper() {
  if (package) {
    delete package;
  }
}

void SkyReaper::interceptPackage() {
  srand(time(0));
  Package* base = dynamic_cast<Package*>(target->getPackage());
  PackageEncryptionDecorator* p = new PackageEncryptionDecorator(
      target->getPackage(), model->getEncryption());
  std::string encryption = p->getEncryptionType();
  // std::cout << encryption << std::endl;
  if (!p) {
    std::cout << "Error: Package is null" << std::endl;
  }
  // std::cout << "Entered intercept package function" << std::endl;
  bool result;
  if (encryption == "obelisk-9") {
    result = (rand() % 100) < 2;
  } else if (encryption == "chrono-lattice") {
    result = (rand() % 100) < 39;
  } else if (encryption == "helix-vortex") {
    result = (rand() % 100) < 55;
  } else {
    result = true;
  }

  if (result) {
    target->takePackage();
    Package* p2 = target->getPackage();
    if (p2 == nullptr) {
      std::cout << "target package stolen" << std::endl;
      DataManager::getInstance().lostPackages(target->getId());
    }
    std::string msg = "Successful in cracking package";
    notifyObservers(msg);
    package = p;
  } else {
    std::string msg = "Cracking attempt unsuccessful";
    notifyObservers(msg);
  }
  target = nullptr;
}

void SkyReaper::update(double dt) {
  if (target) {
    toDrone->move(this, dt);
    double diff = target_pos.dist(this->position);
    if (diff < 300.0) {
      std::string msg = "Sky Reaper intercepting drone...";
      notifyObservers(msg);
      this->interceptPackage();
    }
    // if (toDrone->isCompleted()) {
    //  target = nullptr; ADD THIS TO INTERCEPT PACKAGE
    // std::cout << "Sky Reaper has reached the drone" << std::endl;
    // this->interceptPackage();
    //}
  }
}

void SkyReaper::notifyPosition(const Vector3& location, Drone* d) {
  // std::cout << "inside sky reaper positoin... " << std::endl;
  double dist = this->getPosition().dist(location);
  if (dist < this->radius) {
    if (!target && !toDrone) {
      target = d;
      Vector3 target_direction = target->getDirection();
      setDirection(target_direction);
      toDrone = new BfsStrategy(position, target_direction, model->getGraph());
    }
  }
}
