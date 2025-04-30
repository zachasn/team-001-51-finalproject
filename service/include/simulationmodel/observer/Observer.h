#ifndef OBSERVER_H_ 
#define OBSERVER_H_ 

#include "IObserver.h"
#include <string>
#include <iostream> 
#include "math/vector3.h"
#include "Publisher.h"

class Publisher;

class Observer {
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void notifyPosition(const Vector3& location, const Publisher* p) = 0;
};

#endif