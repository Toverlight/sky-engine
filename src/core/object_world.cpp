#include "object_world.h"
#include "scene.h"
#include "game.h"
#include "util.h"

void ObjectWorld::init()
{
    ObjectScreen::init();
}

bool ObjectWorld::handleEvents(SDL_Event &event)
{
    ObjectScreen::handleEvents(event);
    return false;
}

void ObjectWorld::update(float dt)
{
    ObjectScreen::update(dt);
    
}

void ObjectWorld::render()
{
    ObjectScreen::render();
}

glm::vec2 ObjectWorld::getPosScreen()
{
    if (!_is_pos_screen_dirty) return _pos_screen;
    _is_pos_screen_dirty = false;
    Camera& camera = Game::getInstance().getCurrentScene()->getCamera();
    // 根据屏幕分辨率、相机位置、相机缩放、相机旋转和世界坐标计算屏幕坐标
    return rotateVec2(_pos_world - camera.position, -camera.rotation) * camera.zoom + Game::getInstance().getResolution() / 2.0f;
}

void ObjectWorld::setPosScreen(const glm::vec2 &pos)
{
    _pos_screen = pos;
    _is_pos_world_dirty = true;
    _is_pos_screen_dirty = false;
}

glm::vec2 ObjectWorld::getPosWorld()
{
    if (!_is_pos_world_dirty) return _pos_world;
    _is_pos_world_dirty = false;
    Camera& camera = Game::getInstance().getCurrentScene()->getCamera();
    // 根据屏幕分辨率、相机位置、相机缩放、相机旋转和屏幕坐标计算世界坐标
    return rotateVec2((_pos_screen - Game::getInstance().getResolution() / 2.0f) / camera.zoom, camera.rotation) + camera.position;
}

void ObjectWorld::setPosWorld(const glm::vec2 &pos)
{
    _pos_world = pos;
    _is_pos_screen_dirty = true;
    _is_pos_world_dirty = false;
}
