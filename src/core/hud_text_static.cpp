#include "hud_text_static.h"
#include "text_label.h"

HUD_TextStatic* HUD_TextStatic::create(const std::string& text, const glm::vec2& pos_screen, const std::string& font_path, const std::string& bg_path, const glm::vec2& padding, int font_size, SDL_FColor color)
{
    auto hud_text_static = new HUD_TextStatic();
    hud_text_static->init();
    hud_text_static->setPosScreen(pos_screen);
    hud_text_static->setPadding(padding);
    auto background_sprite = Sprite::createAndAffiliate(hud_text_static, bg_path);
    auto text_label = TextLabel::createAndAffiliate(hud_text_static, text, font_path, font_size, color);
    hud_text_static->setBackgroundSprite(background_sprite);
    hud_text_static->setTextLabel(text_label);
    return hud_text_static;
}

void HUD_TextStatic::update(float dt)
{
    ObjectScreen::update(dt);
    refreshBackgroundSpriteSize();
}

void HUD_TextStatic::setTextLabel(TextLabel* text_label)
{
    _text_label = text_label;
    _is_background_sprite_dirty = true;
}

void HUD_TextStatic::setBackgroundSprite(Sprite* background_sprite)
{
    _background_sprite = background_sprite;
    _is_background_sprite_dirty = true;
}

void HUD_TextStatic::setPadding(const glm::vec2& padding)
{
    _padding = padding;
    _is_background_sprite_dirty = true;
}

TextLabel* HUD_TextStatic::getTextLabel()
{
    if (_text_label) _text_label->refreshTextSize();
    _is_background_sprite_dirty = true;
    return _text_label;
}

void HUD_TextStatic::refreshBackgroundSpriteSize()
{
    if (_is_background_sprite_dirty && _background_sprite && _text_label)
    {
        _is_background_sprite_dirty = false;
        auto text_size = getTextLabel()->getSize();
        auto background_size = text_size + _padding * 2.0f; // 内边距
        _background_sprite->setSize(background_size);
    }
}