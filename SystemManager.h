#ifndef SYSTEMSMANAGER_H
#define SYSTEMSMANAGER_H

#include <vector>
#include <memory>
#include "System.h"
#include"CameraSystem.h"
class SystemsManager {
private:
    std::vector<std::shared_ptr<System>> systems;

public:
    template<typename T, typename... Args>
    void addSystem(Args&&... args) {
        systems.push_back(std::make_shared<T>(std::forward<Args>(args)...));
    }

    void update(float deltaTime) {
        for (auto& system : systems) {
            system->update( deltaTime);
        }
    }

    void lateUpdate(float deltaTime) {
        for (auto& system : systems) {
            system->lateUpdate(deltaTime);
        }
    }
};

#endif // SYSTEMSMANAGER_H
