#include<iostream>
#include<typeinfo>
#include<vector>

using Entity = unsigned int;
class EntityManager {
	std::vector<Entity>availableEntities;
	unsigned int nextEntityID = 0;

public:
	Entity createEntity() {
		if (availableEntities.empty()) {
			return nextEntityID++;

		}
		else {
			Entity id = availableEntities.back();
			availableEntities.pop_back();
			return id;
		}
		
		
	}void destroyEntity(Entity entity) {
		availableEntities.push_back(entity);
	}
};