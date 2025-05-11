#include "camera.h"
#include "scene.h"

void Camera::setPosition(const glm::vec2 &pos)
{
    position = pos;
    informModificationToScene();
}

void Camera::setZoom(float z)
{
    zoom = z;
    informModificationToScene();
}

void Camera::setRotation(float r)
{
    rotation = r;
    informModificationToScene();
}

void Camera::informModificationToScene()
{
    if (scene) scene->toSetCameraDirty();
}