#include "MovementSystem.h"
#include "ComponentManager.h"

void MovementSystem::update(ComponentManager& components, float deltaTime) {
    for (Entity entity : entities) {
        auto transform = components.getComponent<TransformComponent>(entity);
        auto velocity = components.getComponent<VelocityComponent>(entity);

        if (transform && velocity) {
            transform->position += velocity->velocity * deltaTime;
        }
    }
}
