#pragma once

#include "object_screen.h"
#include "text_label.h"
#include "sprite.h"

class HUD_TextStatic : public ObjectScreen
{
protected://TODO: 新类HUD_TextSpliced.背景精灵采用九宫格式拼接防止边框变形
    TextLabel* _text_label = nullptr; // 文本标签
    Sprite* _background_sprite = nullptr; // 背景精灵
    glm::vec2 _padding = glm::vec2(0, 0); // 内边距
    bool _is_background_sprite_dirty = true; // 背景精灵是否脏

public:
    HUD_TextStatic() = default;
    virtual ~HUD_TextStatic() = default;

    static HUD_TextStatic* create(const std::string& text, const glm::vec2& pos_screen, const std::string& font_path, const std::string& bg_path, const glm::vec2& padding = glm::vec2(0, 0), int font_size = 16, SDL_FColor color = { 1.0f, 1.0f, 1.0f, 1.0f });

    virtual void update(float dt) override;

    void setTextLabel(TextLabel* text_label);
    void setBackgroundSprite(Sprite* background_sprite);
    void setPadding(const glm::vec2& padding);
    TextLabel* getTextLabel();

    void refreshBackgroundSpriteSize();

};
