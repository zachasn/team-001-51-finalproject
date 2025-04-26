#include "PackageEncryptionDecorator.h" 

PackageEncryptionDecorator::PackageEncryptionDecorator(Package* p, std::string encryption) : PackageDecorator(p), encryptionType(encryption) {} 

std::string PackageEncryptionDecorator::getEncryptionDetails() const {
    std::cout << encryptionType << std::endl;
    if (encryptionType == "obelisk-9") {
        return "Multi-dimensional hashing grids for fragmentation.";
    } else if (encryptionType == "chrono-lattice") {
        return "Time-dependent quantum lattice encryption.";
    } else if (encryptionType == "helix-vortex") {
        return "Recursive spiral-pattern bit shifts.";
    } else {
        return "Invalid encrpytion type or null type, package is not encrypted.";
    }
}

void PackageEncryptionDecorator::setEncryptionDetails(std::string encrpytion) {
    encryptionType = encrpytion;
}

bool PackageEncryptionDecorator::rand() {
    std::cout << "Inside the rand function";
    return false;
}
