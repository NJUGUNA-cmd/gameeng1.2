#ifndef SYSTEMMANAGER_TPP
#define SYSTEMMANAGER_TPP

#include "SystemManager.h"

template <typename T, typename... Args>
T* SystemManager::addSystem(Args&&... args) {
    systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    return static_cast<T*>(systems.back().get());
}

#endif // SYSTEMMANAGER_TPP
