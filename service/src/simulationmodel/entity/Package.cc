#include "Package.h"

#include "Robot.h"

// Static member initialization
int Package::next_index_ = 0;

Package::Package(const JsonObject& obj)
    : IEntity(obj),
      priority_context_(new PriorityShippingContext()),
      is_picked_up_(false),
      is_delivered_(false),
      order_index_(next_index_++) {
  // Parse destination from JSON
  if (obj.contains("position")) {
    JsonArray pos = obj["position"];
    destination = Vector3(pos[0], pos[1], pos[2]);
  }
  // Parse name
  if (obj.contains("name")) {
    name = static_cast<std::string>(obj["name"]);
  }
}

Package::~Package() { delete priority_context_; }

Vector3 Package::getDestination() const { return destination; }

std::string Package::getStrategyName() const { return strategyName; }

Robot* Package::getOwner() const { return owner; }

bool Package::requiresDelivery() const { return requiresDelivery_; }

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::update(double dt) {}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery_ = false;
  destination = owner->getPosition();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

void Package::linkModel(
    SimulationModel* model) {  // CHANGE: ADDED TO MATCH IEntity
  this->model = model;
}

bool Package::setPriority(int priority, NotificationSystem* notifier) {
  // Check if package is not picked up or delivered
  if (!is_picked_up_ && !is_delivered_) {
    priority_context_->changeState(priority, notifier,
                                   this);  // CHANGE: ADDED this FOR changeState
    return true;
  }
  // Notify error if notifier exists
  if (notifier) {
    std::string message = "Error: Cannot change priority for package ";
    message = message + std::to_string(getId()) + " after pickup or delivery";
    notifier->publish(message);
  }
  return false;  // CHANGE: MOVED RETURN OUTSIDE if
}

int Package::getPriorityLevel() const {
  return priority_context_->getPriorityLevel();
}

std::string Package::getPriorityName() const {
  return priority_context_->getName();
}
