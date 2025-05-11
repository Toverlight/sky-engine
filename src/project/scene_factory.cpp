#include "scene_factory.h"

Scene *SceneFactory::createScene(const std::string &sceneName)
{
    if (sceneName == "SceneInit") {
        return new SceneInit();
    }
    return nullptr;
}
