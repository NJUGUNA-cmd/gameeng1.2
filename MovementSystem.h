#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "System.h"

class MovementSystem : public System {
public:
    void update(ComponentManager& components, float deltaTime) override;
};

#endif // MOVEMENTSYSTEM_H
