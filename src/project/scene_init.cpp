#include "scene_init.h"

void SceneInit::init()
{
    Scene::init();
    SDL_Log("SceneInit initialized.");
}

bool SceneInit::handleEvents(SDL_Event &event)
{
    return Scene::handleEvents(event);
}

void SceneInit::update(float dt)
{
    Scene::update(dt);
}

void SceneInit::render()
{
    Scene::render();
    
}
