#ifndef OBSERVER_H_ 
#define OBSERVER_H_ 

#include "IObserver.h"
#include <string>
#include <iostream> 
#include "math/vector3.h"

class Observer {
public:
    Observer() {}
    virtual ~Observer() {}
    void notifyPosition(const Vector3& position) const {
        std::cout << "Current position ... " << std::endl;
    }
};

#endif