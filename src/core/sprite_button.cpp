#include "sprite_button.h"

SpriteButton* SpriteButton::create(const std::string& idle_sprite_path, const std::string& hover_sprite_path, const std::string& pressed_sprite_path, const glm::vec2& size)
{
    SpriteButton* button = new SpriteButton();
    button->init();
    button->setIdleSprite(idle_sprite_path);
    button->setHoverSprite(hover_sprite_path);
    button->setPressedSprite(pressed_sprite_path);
    button->setSize(size);
    if (button->_idle_sprite) button->_idle_sprite->setActive(true);
    if (button->_hover_sprite) button->_hover_sprite->setActive(false);
    if (button->_pressed_sprite) button->_pressed_sprite->setActive(false);
    return button;
}

void SpriteButton::init()
{
    RectButton::init();
}

void SpriteButton::update(float dt)
{
    if (_is_sprite_size_dirty) {
        if (_idle_sprite) _idle_sprite->setSize(_size);
        if (_hover_sprite) _hover_sprite->setSize(_size);
        if (_pressed_sprite) _pressed_sprite->setSize(_size);
        _is_sprite_size_dirty = false;
    }
    RectButton::update(dt);

    if (_is_pressed) {
        if (_pressed_sprite) _pressed_sprite->setActive(true);
        if (_idle_sprite) _idle_sprite->setActive(false);
        if (_hover_sprite) _hover_sprite->setActive(false);
    }
    else if (_is_hovered) {
        if (_hover_sprite) _hover_sprite->setActive(true);
        if (_idle_sprite) _idle_sprite->setActive(false);
        if (_pressed_sprite) _pressed_sprite->setActive(false);
    }
    else {
        if (_idle_sprite) _idle_sprite->setActive(true);
        if (_hover_sprite) _hover_sprite->setActive(false);
        if (_pressed_sprite) _pressed_sprite->setActive(false);
    }
}

void SpriteButton::setSize(const glm::vec2& size)
{
    _size = size;
    _is_sprite_size_dirty = true;
}

void SpriteButton::setIdleSprite(const std::string& sprite_path)
{
    if (_idle_sprite) {
        _idle_sprite->toRemove();
        _idle_sprite = nullptr;
    }
    _idle_sprite = Sprite::createAndAffiliate(this, sprite_path);
    _is_sprite_size_dirty = true;
}

void SpriteButton::setHoverSprite(const std::string& sprite_path)
{
    if (_hover_sprite) {
        _hover_sprite->toRemove();
        _hover_sprite = nullptr;
    }
    _hover_sprite = Sprite::createAndAffiliate(this, sprite_path);
    _is_sprite_size_dirty = true;
}

void SpriteButton::setPressedSprite(const std::string& sprite_path)
{
    if (_pressed_sprite) {
        _pressed_sprite->toRemove();
        _pressed_sprite = nullptr;
    }
    _pressed_sprite = Sprite::createAndAffiliate(this, sprite_path);
    _is_sprite_size_dirty = true;
}
