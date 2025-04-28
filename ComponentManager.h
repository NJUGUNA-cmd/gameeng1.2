#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include "Entity.h"

template<typename T>
class ComponentManager {

public:
	//add component to the specified entity
	void addComponent(Entity entity, T component) {
		components[entity.getId()] = component;
	}
	//Retrieves a reference to the component associated with the entity
	T& getComponent(Entity entity) {
		return components.at(entity.getId());//using at()for bounds checking
	}
	//removes a reference to the component associated with entity
	void removeComponent(Entity entity) {
		components.erase(entity.getId());
	}
	//returns a refrence to the map of all components
	std::unordered_map<unsigned int, T>& getAllComponents() {
		return components;
	}
private:
	//stores components with entity IDS as keys
	std::unordered_map<unsigned int, T >components;
};

#endif // COMPONENTMANAGER_H
