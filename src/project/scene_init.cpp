#include "scene_init.h"
#include "../core/sprite.h"
#include "startup_config.h"

void SceneInit::init()
{
    Scene::init();
    ObjectScreen* test_show = new ObjectScreen();
    test_show->init();
    StartupConfig& config = StartupConfig::getInstance();
    test_show->setPosScreen(glm::vec2(config.window_width / 2, config.window_height / 2));
    toAddChild(test_show);
    auto sprite = Sprite::createAndAffiliate(test_show, "assets/test/koisi.png");
    sprite->setScale(glm::vec2(0.25f));
    SDL_Log("SceneInit initialized.\n");
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
