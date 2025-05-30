// Generative AI model: GPT-4o was utilized to assist in writing this Doxygen
// documentation

#ifndef PACKAGE_DECORATOR_H_
#define PACKAGE_DECORATOR_H_

#include "IEntityDecorator.h"
#include "Package.h"
#include "Robot.h"

/**
 * @class PackageDecorator
 * @brief Decorator class that extends the functionality of a Package entity.
 *
 * This class implements the Decorator design pattern to allow additional
 * behavior to be added to Package objects at runtime without modifying their
 * structure. All method calls are forwarded to the underlying Package unless
 * explicitly overridden.
 */
class PackageDecorator : public IEntityDecorator<Package> {
 public:
  /**
   * @brief Constructs a PackageDecorator that wraps a Package instance.
   * @param p Pointer to the Package to be decorated.
   */
  PackageDecorator(Package* p) : IEntityDecorator(p) {}

  /**
   * @brief Gets the destination of the package.
   * @return A Vector3 representing the destination coordinates.
   */
  virtual Vector3 getDestination() const { return sub->getDestination(); };

  /**
   * @brief Gets the name of the delivery strategy used for this package.
   * @return A string representing the delivery strategy.
   */
  virtual std::string getStrategyName() const {
    return sub->getStrategyName();
  };

  /**
   * @brief Gets the robot currently assigned to deliver this package.
   * @return Pointer to the Robot assigned to the package, or nullptr if
   * unassigned.
   */
  virtual Robot* getOwner() const { return sub->getOwner(); };

  /**
   * @brief Checks whether this package still requires delivery.
   * @return True if the package requires delivery; false otherwise.
   */
  virtual bool requiresDelivery() const { return sub->requiresDelivery(); };

  /**
   * @brief Sets the delivery strategy name for this package.
   * @param strategyName_ The name of the strategy to assign.
   */
  virtual void setStrategyName(std::string strategyName_) override {
    sub->setStrategyName(strategyName_);
  };

  /**
   * @brief Initializes the delivery by assigning an owner (Robot) to the
   * package.
   * @param owner Pointer to the Robot that will deliver the package.
   */
  virtual void initDelivery(Robot* owner) override {
    sub->initDelivery(owner);
  };

  /**
   * @brief Performs the handoff process for the package.
   */
  virtual void handOff() override { sub->handOff(); };
};

#endif
