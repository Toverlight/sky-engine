#include "scene_init.h"
#include "../core/sprite.h"
#include "startup_config.h"
#include "../core/util.h"

void SceneInit::init()
{
    Scene::init();
    ObjectScreen* test_show = new ObjectScreen();
    test_show->init();
    StartupConfig& config = StartupConfig::getInstance();
    test_show->setPosScreen(glm::vec2(config.window_width / 2, config.window_height / 2));
    toAddChild(test_show);
    auto sprite = Sprite::createAndAffiliate(test_show, "assets/test/koisi.png");
    sprite->setScale(glm::vec2(1.0f));
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
    Graphics::renderFilledPolygon({{0, 0}, {300, 100}, {300, 300}, {0, 300}}, {0, 1, 0, 1});
    Graphics::renderLine({0, 0}, {300, 300}, {1, 0, 0, 1}, 5);
    Graphics::renderPolygonOutline({{50, 480}, {800, 560}, {900, 700}, {500, 700}}, {0, 0, 1, 1}, 5);
}
