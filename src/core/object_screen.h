#pragma once
#include <glm/glm.hpp>
#include "object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 _pos_screen = glm::vec2(0); // 屏幕坐标
public:
    ObjectScreen() = default;
    virtual ~ObjectScreen() = default;

    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;

    virtual glm::vec2 getPosScreen() { return _pos_screen; }
    virtual void setPosScreen(const glm::vec2& pos) { _pos_screen = pos; }
};