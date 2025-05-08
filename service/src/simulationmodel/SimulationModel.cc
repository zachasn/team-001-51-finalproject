#include "SimulationModel.h"

#include "DataManager.h"
#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageEncryptionDecorator.h"
#include "PackageFactory.h"
#include "RobotFactory.h"
#include "SkyReaper.h"
SimulationModel::SimulationModel(IController& controller,
                                 NotificationSystem* notifier)
    : controller(controller), notifier_(notifier) {
  entityFactory.addFactory(new DroneFactory());
  entityFactory.addFactory(new PackageFactory());
  entityFactory.addFactory(new RobotFactory());
  entityFactory.addFactory(new HumanFactory());
  entityFactory.addFactory(new HelicopterFactory());
      
  scheduler_ = new TripScheduler(notifier_);
  queue_ = new ShippingQueue();
      
  weather = WeatherControl::GetInstance();
  weather->addObserver(this);
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
  delete scheduler_;
  delete queue_;
}

IEntity* SimulationModel::createEntity(const JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];

  // Nayak's version start
  std::string type = "";
  if (entity.contains("type")) {
    type = static_cast<std::string>(entity["type"]);
    ;
  }
  // Nayak's version end

  // previously was
  // std::string type = entity["type"];

  std::cout << "type: " << type << std::endl;
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;

  std::cout << name << std::endl;
  if (entity.contains("encryption")) {
    std::string c = entity["encryption"];
    std::cout << "Contains encryption" << std::endl;
    std::cout << c << std::endl;
  }
  if (name == "SkyReaper") {
    SkyReaper* temp = new SkyReaper(entity);
    adversary = temp;
    myNewEntity = temp;
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
    myNewEntity->addObserver(this);
  } else if (myNewEntity = entityFactory.createEntity(entity)) {

    // ignore package and robot entities
    if (type != "package" && type != "robot") {
      DataManager::getInstance().addEntity(myNewEntity->getId(), name, type);
    }

  // Nayak's addition start
  
    // Hnadling package priority
    if (type == "package") {  // CHANGE: ADDED FOR PRIORITY
      Package* package = dynamic_cast<Package*>(myNewEntity);
      if (package && entity.contains("priority")) {
        int priority = static_cast<int>(entity["priority"]);
        package->setPriority(priority, notifier_);
        if (notifier_) {
          std::string message = "Created package ";
          message = message + std::to_string(package->getId());
          notifier_->publish(message);
          notifier_->publishToUI(message);
        }
      }
    }
    
  // Nayak's addition end

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

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
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
    queue_->addPackage(package, notifier_);
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);

    std::string encryptionName = details["encryption"];
    this->notify(encryptionName);
    encryptionType = encryptionName;

    if (encryptionName != "None") {
      PackageEncryptionDecorator* DecPackage =
          new PackageEncryptionDecorator(package, encryptionName);
      package = DecPackage;
      scheduledDeliveries.push_back(package);
      controller.sendEventToView("DeliveryScheduled", details);
      if (notifier_) {  // CHANGE: ADDED FOR NOTIFICATIONS
        std::string message = "Scheduled delivery for package ";
        message = message + std::to_string(package->getId());
        notifier_->publish(message);
        notifier_->publishToUI(message);
      }
      std::vector<Robot*> robots;  // CHANGE: ADDED FOR PRIORITY SCHEDULING
      for (auto& [id, entity] : entities) {
        Robot* robot = dynamic_cast<Robot*>(entity);
        if (robot) {
          robots.push_back(robot);
        }
      }
      scheduler_->assignPackages(robots, *queue_);
      return;
    }

    entityFactory.createEntity(details);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
    if (notifier_) {  // CHANGE: ADDED FOR NOTIFICATIONS
      std::string message = "Scheduled delivery for package ";
      message = message + std::to_string(package->getId());
      notifier_->publish(message);
      notifier_->publishToUI(message);
    }
    std::vector<Robot*> robots;  // CHANGE: ADDED FOR PRIORITY SCHEDULING
    for (auto& [id, entity] : entities) {
      Robot* robot = dynamic_cast<Robot*>(entity);
      if (robot) {
        robots.push_back(robot);
      }
    }
    scheduler_->assignPackages(robots, *queue_);
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
  weather->update(dt);
}

void SimulationModel::stop(void) {}

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    Package* pkg = dynamic_cast<Package*>(entity);
    if (pkg) {
      queue_->removePackage(pkg, notifier_);
      for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
           ++i) {
        if (*i == entity) {
          scheduledDeliveries.erase(i);
          break;
        }
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

DroneObserver* SimulationModel::getAdversary() { return adversary; }

std::string SimulationModel::getEncryption() { return encryptionType; }