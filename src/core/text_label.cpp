#include <SDL3_ttf/SDL_ttf.h>
#include "text_label.h"
#include "object_affiliate.h"
#include "util.h"

TextLabel::~TextLabel()
{
    if (_ttf_text)
    {
        TTF_DestroyText(_ttf_text);
        _ttf_text = nullptr;
    }
}

TextLabel* TextLabel::createAndAffiliate(ObjectScreen* parent, const std::string& text, const std::string& font_path, int font_size, SDL_FColor color, Anchor anchor)
{
    auto text_label = new TextLabel();
    text_label->init();
    text_label->setParent(parent);
    text_label->setFont(font_path, font_size);
    text_label->setText(text);
    text_label->setColor(color);
    text_label->setAnchor(anchor);
    if (parent) parent->toAddChild(text_label);
    return text_label;
}

void TextLabel::update(float dt)
{
    ObjectAffiliate::update(dt);
    refreshTextSize();
}

void TextLabel::render()
{
    ObjectAffiliate::render();
    auto pos = _parent->getPosScreen() + getOffset();
    TTF_SetTextColorFloat(_ttf_text, _color.r, _color.g, _color.b, _color.a);
    TTF_DrawRendererText(_ttf_text, pos.x, pos.y);
}

void TextLabel::setFont(const std::string& font_path, int font_size)
{
    _font_path = font_path;
    _font_size = font_size;
    auto font = Game::getInstance().getAssetStore()->getFont(font_path, font_size);
    if (!_ttf_text) _ttf_text = Text::createTTF_Text("", font_path, font_size);
    TTF_SetTextFont(_ttf_text, font);
    _is_size_dirty = true;
}

void TextLabel::setFontPath(const std::string& font_path)
{
    _font_path = font_path;
    auto font = Game::getInstance().getAssetStore()->getFont(font_path, _font_size);
    TTF_SetTextFont(_ttf_text, font);
    _is_size_dirty = true;
}

void TextLabel::setFontSize(int font_size)
{
    _font_size = font_size;
    auto font = Game::getInstance().getAssetStore()->getFont(_font_path, font_size);
    TTF_SetTextFont(_ttf_text, font);
    _is_size_dirty = true;

}

void TextLabel::setText(const std::string& text)
{
    TTF_SetTextString(_ttf_text, text.c_str(), text.length());
    _is_size_dirty = true;
}

void TextLabel::refreshTextSize()
{
    if (_is_size_dirty)
    {
        _is_size_dirty = false;
        int w, h;
        TTF_GetTextSize(_ttf_text, &w, &h);
        setSize(glm::vec2(w, h));
    }
}