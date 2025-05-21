#pragma once

#include "rect_button.h"
#include "sprite.h"
#include <string>

class SpriteButton : public RectButton
{
protected:
    Sprite* _idle_sprite = nullptr;
    Sprite* _hover_sprite = nullptr;
    Sprite* _pressed_sprite = nullptr;

    bool _is_sprite_size_dirty = true;

public:
    SpriteButton() = default;
    virtual ~SpriteButton() = default;

    static SpriteButton* create(const std::string& idle_sprite_path, const std::string& hover_sprite_path, const std::string& pressed_sprite_path, const glm::vec2& size = glm::vec2(0));

    virtual void init() override;
    virtual void update(float dt) override;

    virtual void setSize(const glm::vec2& size) override;

    void setIdleSprite(const std::string& sprite_path);
    void setHoverSprite(const std::string& sprite_path);
    void setPressedSprite(const std::string& sprite_path);

};