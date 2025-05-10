#include "object_screen.h"

void ObjectScreen::init()
{
    Object::init();
}

bool ObjectScreen::handleEvents(SDL_Event &event)
{
    Object::handleEvents(event);
    return false;
}

void ObjectScreen::update(float dt)
{
    Object::update(dt);
}

void ObjectScreen::render()
{
    Object::render();
}
