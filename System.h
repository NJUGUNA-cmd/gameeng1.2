#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "ComponentManager.h"

class System {
public:
    virtual void update(float deltaTime)=0;
    virtual ~System() = default;

    void lateUpdate(float deltaTime) {}

};

#endif // SYSTEM_H
