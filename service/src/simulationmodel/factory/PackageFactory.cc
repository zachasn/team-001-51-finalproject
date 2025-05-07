#include "PackageFactory.h"

#include "PackageEncryptionDecorator.h"

IEntity* PackageFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("package") == 0) {
    // Package* p = new Package(entity);
    std::cout << "Package Created" << std::endl;
    return new PackageEncryptionDecorator(new Package(entity));
  }
  return nullptr;
}
