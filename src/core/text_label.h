#pragma once
#include "object_affiliate.h"
#include "object_screen.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class TextLabel : public ObjectAffiliate
{
protected:
    TTF_Text* _ttf_text = nullptr; // TTF文本对象
    std::string _font_path; // 字体路径
    int _font_size = 16; // 字体大小
    bool _is_size_dirty = true; // 文本标签大小是否脏
    SDL_FColor _color = { 1.0f, 1.0f, 1.0f, 1.0f }; // 文本颜色

public:
    TextLabel() = default;
    virtual ~TextLabel();

    static TextLabel* createAndAffiliate(ObjectScreen* parent, const std::string& text, const std::string& font_path, int font_size = 16, SDL_FColor color = { 1.0f, 1.0f, 1.0f, 1.0f }, Anchor anchor = Anchor::CENTER);

    virtual void update(float dt) override;
    virtual void render() override;

    void setFont(const std::string& font_path, int font_size);
    void setFontPath(const std::string& font_path);
    void setFontSize(int font_size);
    void setText(const std::string& text);
    void setColor(const SDL_FColor& color) { _color = color; }
    int getFontSize() const { return _font_size; }
    std::string getText() const { return _ttf_text ? _ttf_text->text : ""; }
    SDL_FColor getColor() const { return _color; }

    void refreshTextSize();
};