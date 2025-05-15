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
    // TODO: 添加文本颜色属性

public:
    TextLabel() = default;
    virtual ~TextLabel();

    static TextLabel* createAndAffiliate(ObjectScreen* parent, const std::string& text, const std::string& font_path, int font_size = 16, Anchor anchor = Anchor::CENTER);

    virtual void update(float dt) override;
    virtual void render() override;

    void setFont(const std::string& font_path, int font_size);
    void setFontPath(const std::string& font_path);
    void setFontSize(int font_size);
    void setText(const std::string& text);
    int getFontSize() const { return _font_size; }
    std::string getText() const { return _ttf_text ? _ttf_text->text : ""; }
};