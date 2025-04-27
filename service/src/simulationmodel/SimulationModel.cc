#include "SimulationModel.h"

#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"
#include "SkyReaper.h"
#include "Publisher.h";

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.addFactory(new DroneFactory());
  entityFactory.addFactory(new PackageFactory());
  entityFactory.addFactory(new RobotFactory());
  entityFactory.addFactory(new HumanFactory());
  entityFactory.addFactory(new HelicopterFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

IEntity* SimulationModel::createEntity(const JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  std::cout << name << std::endl;
  if (name == "SkyReaper") {
    SkyReaper* temp = new SkyReaper(entity);
    adversary = temp;
    myNewEntity = temp;
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
    myNewEntity->addObserver(this);
  } else if (myNewEntity = entityFactory.createEntity(entity)) {
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
    // Add the simulation model as a observer to myNewEntity
    myNewEntity->addObserver(this);
  }
  /*
  std::string encryptionName = details["encryption"];
  this->notify(encryptionName);
  if (details.contains("encryption")) {
    std::string encryptionName = details["encryption"];
    this->notify(encryptionName);
  } else {
      std::cout << "Warning: No 'encryption' key" << std::endl;
  } */
  return myNewEntity;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(const JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  for (const auto& key : details.getKeys()) {
    std::cout << key << std::endl;
  } 

  Package* package = nullptr;
  /*
  PackageFactory factory;
  IEntity* entity2 = factory.createEntity(details);
  Package* BasePackage = dynamic_cast<Package*>(entity2);
  std::cout << "Made it here (3)" << std::endl;
  PackageEncryptionDecorator* Decpackage = new PackageEncryptionDecorator(BasePackage);
  Package* package = Decpackage;  
  */

  for (auto& [id, entity]: entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery()) {
          package = p;
          break;
        }
      }
    }
  } 

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    
    std::string encryptionName = details["encryption"];
    this->notify(encryptionName);
    if (encryptionName != "None") {
      PackageEncryptionDecorator* DecPackage = new PackageEncryptionDecorator(package, encryptionName);
      package = DecPackage;
      std::cout << DecPackage->getEncryptionDetails() << std::endl;
      scheduledDeliveries.push_back(package);
      controller.sendEventToView("DeliveryScheduled", details);
      return;
    }
    
    entityFactory.createEntity(details);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::Graph* SimulationModel::getGraph() const { return graph; }

void SimulationModel::setGraph(const routing::Graph* graph) {
  if (this->graph) delete this->graph;
  this->graph = graph;
}

/// Updates the simulation
void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::stop(void) {}

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

void SimulationModel::notify(const std::string& message) const {
  JsonObject details;
  details["message"] = message;
  this->controller.sendEventToView("Notification", details);
}

Observer* SimulationModel::getAdversary() {
  return adversary;
}
