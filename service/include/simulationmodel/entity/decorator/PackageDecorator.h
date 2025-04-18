#ifndef PACKAGE_DECORATOR_H_ 
#define PACKAGE_DECORATOR_H_ 

#include "Package.h"
#include "IEntityDecorator.h" 
#include "Robot.h"

class PackageDecorator : public IEntityDecorator<Package>{
public:
    PackageDecorator(Package* p) : IEntityDecorator(p) {} 
    virtual Vector3 getDestination() {return sub->getDestination(); };
    virtual std::string getStrategyName() {return sub->getStrategyName(); };
    virtual Robot* getOwner() {return sub->getOwner(); };
    virtual bool requiresDelivery() {return sub->requiresDelivery(); };
    virtual void setStrategyName(std::string strategyName_) {sub->setStrategyName(strategyName_); };
    virtual void initDelivery(Robot* owner) {sub->initDelivery(owner); };
    virtual void handOff() {sub->handOff(); }; 
};

#endif