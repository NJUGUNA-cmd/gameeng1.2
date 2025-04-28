#ifndef COMPONENTS_TPP
#define COMPONENTS_TPP


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
    glm::vec3 Position;
    glm::vec3 Orientation;
    glm::vec3 Up;
    float speed;
    float sensitivity;
    // Additional related camera data can be added here, such as:
    // float FOV;
    // float sensitivity;
    CameraComponent(Camera& cam):camera(cam),Position(cam.Position), Orientation(cam.Orientation), Up(cam.Up), speed(cam.speed), sensitivity(cam.sensitivity) {}
};

#endif // COMPONENTS_TPP
