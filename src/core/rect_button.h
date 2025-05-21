#pragma once
#include "abstract_button.h"

class RectButton : public AbstractButton
{
protected:
    glm::vec2 _size = glm::vec2(0); // 按钮大小

    virtual bool ifMouseInButtonArea(const glm::vec2& mouse_position) override;
public:
    RectButton() = default;
    virtual ~RectButton() = default;

    virtual void setSize(const glm::vec2& size) { _size = size; }

};