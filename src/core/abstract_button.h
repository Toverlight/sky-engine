#pragma once
#include "object_screen.h"
#include <SDL3/SDL_mouse.h>

class AbstractButton : public ObjectScreen
{
protected:
    bool _is_pressed = false;
    bool _is_hovered = false;
    SDL_MouseButtonFlags _matching_button = SDL_BUTTON_LEFT; // 匹配的鼠标按键
    //TODO: bool _is_enabled = true;
    void (*_onClickCallback)() = nullptr; // 点击回调函数
    void (*_onHoverCallback)() = nullptr; // 悬停回调函数

    virtual void checkButtonState();
    virtual bool ifMouseInButtonArea(const glm::vec2& mouse_position) = 0;

public:
    AbstractButton() = default;
    virtual ~AbstractButton() = default;

    void setMatchingButton(SDL_MouseButtonFlags button) {
        _matching_button = button;
    }

    void setOnClickCallback(void (*callback)()) {
        _onClickCallback = callback;
    }

    void setOnHoverCallback(void (*callback)()) {
        _onHoverCallback = callback;
    }

};
