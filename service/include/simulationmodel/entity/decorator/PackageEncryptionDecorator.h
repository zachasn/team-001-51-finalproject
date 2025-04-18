#ifndef PACKAGE_ENCRYPTION_DECORATOR_H_
#define PACKAGE_ENCRYPTION_DECORATOR_H_

#include "Package.h"
#include "PackageDecorator.h"
#include "Robot.h"

class PackageEncryptionDecorator : public PackageDecorator {
private:
    std::string encryptionType;
public: 
    PackageEncryptionDecorator(Package* p, std::string encryption = "none");
    std::string getEncryptionDetails() const;
    void setEncryptionDetails(std::string encrpytion);
    bool rand(); 
};

#endif