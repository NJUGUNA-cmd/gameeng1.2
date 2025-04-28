#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include "Camera.h"

#include "ComponentManager.h"
#include "Components.hpp"  // Include component definitions

class CameraSystem {
public:
    CameraSystem(ComponentManager<CameraComponent>& cameraManager): cameraManager(cameraManager) {}

    /*void update(GLFWwindow* window) {
        for (auto& pair : cameraManager.getAllComponents()) {
            CameraComponent& camComp = pair.second;
            Camera& camera = camComp.camera;
            camera.Inputs(window);  // `window` needs to be passed to `update`
            camera.updateMatrix(45.0f, 0.1f, 100.0f);
        }
    }*/

private:
    ComponentManager<CameraComponent>& cameraManager;
    
};

#endif // CAMERASYSTEM_H
