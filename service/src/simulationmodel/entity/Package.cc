#include "Package.h"

#include "Robot.h"

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
