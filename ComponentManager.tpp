#ifndef COMPONENTS_TPP
#define COMPONENTS_TPP

#include "glm/glm.hpp"
#include "Camera.h"

struct TransformComponent {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

struct VelocityComponent {
    glm::vec3 velocity;
};

struct CameraComponent {
    Camera camera;
    // Additional related camera data can be added here, such as:
    // float FOV;
    // float sensitivity;
};

#endif // COMPONENTS_TPP
