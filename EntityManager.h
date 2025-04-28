#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "Entity.h"

/*this class manages creation and destruction of entities*/
class EntityManager {
private:
    std::vector<unsigned int> availableEntities;
    unsigned int nextEntityID = 0;

public:
    Entity createEntity() {
        unsigned int id;
        if (!availableEntities.empty()) {
            id = availableEntities.back();//Ensure we remove the ID from the pool

        }
        else {
            id = nextEntityID++;
        }
        return Entity(id);
    }

    void destroyEntity(Entity entity) {
        availableEntities.push_back(entity.getId());//add id back to the pool
    }
};

#endif // ENTITYMANAGER_H
