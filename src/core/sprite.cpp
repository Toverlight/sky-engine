#include "sprite.h"
#include "util.h"

Sprite *Sprite::createAndAffiliate(ObjectScreen *parent, const std::string &texture_path, const glm::vec2& scale, Anchor anchor)
{
    Sprite *sprite = new Sprite();
    sprite->init();
    sprite->setParent(parent);
    sprite->setTexture(Texture(texture_path));
    sprite->setScale(scale);
    sprite->setAnchor(anchor);
    if (parent) parent->toAddChild(sprite);
    return sprite;
}

void Sprite::render()
{
    if (_texture.texture && _parent) {
        Graphics::renderTexture(_texture, _parent->getPosScreen() + getOffset(), getSize());
    }
}

void Sprite::setTexture(const Texture &texture)
{
    _texture = texture;
    _texture.size = glm::vec2(_texture.clip.w, _texture.clip.h);
}
