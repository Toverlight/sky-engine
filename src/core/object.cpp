#include "object.h"
#include "def.h"

Object::~Object()
{
    for (auto child : _children)
    {
        if (child) {
            delete child;
        }
    }
    _children.clear();
}

void Object::init()
{
    _children.reserve(INIT_OBJECT_CHILDREN);
    _to_be_added.reserve(INIT_OBJECT_CHILDREN);
}

bool Object::handleEvents(SDL_Event &event)
{
    for (auto child : _children)
    {
        if (child && child->isActive()) {
            if (child->handleEvents(event)) {
                return true;
            }
        }
    }
    return false;
}

void Object::update(float dt)
{
    if (!_to_be_added.empty()) {
        for (auto child : _to_be_added)
        {
            _children.push_back(child);
        }
        _to_be_added.clear();
    }
    for (auto it = _children.begin(); it != _children.end(); ++it)
    {
        Object* child = *it;
        if (child) {
            if (!child->isActive()) {
                continue;
            }
            if (child->_need_remove) {
                delete child;
                it = _children.erase(it);
                continue;
            }
        } else {
            it = _children.erase(it);
            continue;
        }
        child->update(dt);
    }
}

void Object::render()
{
    for (auto child : _children)
    {
        if (child && child->isActive()) {
            child->render();
        }
    }
}
