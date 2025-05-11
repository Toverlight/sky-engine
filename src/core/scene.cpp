#include "scene.h"
#include "def.h"

void Scene::init()
{
    Object::init();
    _children_screen.reserve(INIT_SCENE_SCREEN_OBJECTS);
    _children_world.reserve(INIT_SCENE_WORLD_OBJECTS);
}

bool Scene::handleEvents(SDL_Event &event)
{
    for (auto child : _children_screen)
    {
        if (child && child->isActive()) {
            if (child->handleEvents(event)) {
                return true;
            }
        }
    }
    if (!_is_paused) {   
        Object::handleEvents(event);
        for (auto child : _children_world)
        {
            if (child && child->isActive()) {
                if (child->handleEvents(event)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Scene::update(float dt)
{
    _camera.is_dirty = _need_camera_dirty;
    _need_camera_dirty = false;
    if (!_to_be_added.empty()) {
        for (auto child : _to_be_added)
        {
            if (child) {
                if (ObjectWorld* world_child = dynamic_cast<ObjectWorld*>(child)) {
                    _children_world.push_back(world_child);
                } else if (ObjectScreen* screen_child = dynamic_cast<ObjectScreen*>(child)) {
                    _children_screen.push_back(screen_child);
                } else {
                    _children.push_back(child);
                }
            }
        }
        _to_be_added.clear();
    }
    if (!_is_paused) {
        for (auto it = _children_world.begin(); it != _children_world.end(); ++it)
        {
            ObjectWorld* child = *it;
            if (child) {
                if (!child->isActive()) {
                    continue;
                }
                if (child->getNeedRemove()) {
                    delete child;
                    it = _children_world.erase(it);
                    continue;
                }
            } else {
                it = _children_world.erase(it);
                continue;
            }
            if (child) {
                child->update(dt);
            }
        }
        for (auto it = _children_screen.begin(); it != _children_screen.end(); ++it)
        {
            ObjectScreen* child = *it;
            if (child) {
                if (!child->isActive()) {
                    continue;
                }
                if (child->getNeedRemove()) {
                    delete child;
                    it = _children_screen.erase(it);
                    continue;
                }
            } else {
                it = _children_screen.erase(it);
                continue;
            }
            if (child) {
                child->update(dt);
            }
        }
        Object::update(dt);
    }
}

void Scene::render()
{
    for (auto child : _children_world)
    {
        if (child && child->isActive()) {
            child->render();
        }
    }
    for (auto child : _children_screen)
    {
        if (child && child->isActive()) {
            child->render();
        }
    }
    Object::render();
}

void Scene::removeChild(Object *child)
{
    if (ObjectWorld* world_child = dynamic_cast<ObjectWorld*>(child)) {
        _children_world.erase(std::remove(_children_world.begin(), _children_world.end(), world_child), _children_world.end());
    } else if (ObjectScreen* screen_child = dynamic_cast<ObjectScreen*>(child)) {
        _children_screen.erase(std::remove(_children_screen.begin(), _children_screen.end(), screen_child), _children_screen.end());
    } else {
        Object::removeChild(child);
    }
}
