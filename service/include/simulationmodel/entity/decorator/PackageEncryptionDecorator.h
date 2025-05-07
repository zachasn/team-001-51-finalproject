#ifndef PACKAGE_ENCRYPTION_DECORATOR_H_
#define PACKAGE_ENCRYPTION_DECORATOR_H_

#include "Package.h"
#include "PackageDecorator.h"
#include "Robot.h"

/**
* @class PackageEncryptionDecorator 
* @brief Adds encryption to the package 
*/
class PackageEncryptionDecorator : public PackageDecorator {
 private:
  std::string encryptionType;

 public:
 /**
 * @brief Decorator wrapper that adds encryption to the package 
 * @param p Pointer to the package being wrapped 
 * @param encryption A string representing the encryption type being used
 */
  PackageEncryptionDecorator(Package* p, std::string encryption = "none");
  /**
  * @brief Prints the details of the encryption
  */
  std::string getEncryptionDetails() const;
  /**
  * @brief Sets the encryption type of the package
  * @param encryption String representing encryption type
  */
  void setEncryptionDetails(std::string encryption);
  /**
  * @brief Returns the encryption type 
   */
  std::string getEncryptionType() const;
};

#endif