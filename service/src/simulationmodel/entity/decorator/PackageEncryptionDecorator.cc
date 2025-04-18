#include "PackageEncryptionDecorator.h" 

PackageEncryptionDecorator::PackageEncryptionDecorator(Package* p, std::string encryption) : PackageDecorator(p), encryptionType(encryption) {} 

std::string PackageEncryptionDecorator::getEncryptionDetails() const {
    if (encryptionType == "Obelisk-9 Mesh Lock") {
        return "Multi-dimensional hashing grids for fragmentation.";
    } else if (encryptionType == "Chrono-Lattice Cipher") {
        return "Time-dependent quantum lattice encryption.";
    } else if (encryptionType == "Helix-Vortex Encoding") {
        return "Recursive spiral-pattern bit shifts.";
    } else {
        return "Invalid encrpytion type or null type, package is not encrypted.";
    }
}

void PackageEncryptionDecorator::setEncryptionDetails(std::string encrpytion) {
    encryptionType = encrpytion;
}

bool PackageEncryptionDecorator::rand() {
    return false;
}
