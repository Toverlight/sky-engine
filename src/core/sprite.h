#pragma once

#include <string>
#include "object_affiliate.h"
#include "texture.h"

class Sprite : public ObjectAffiliate
{
protected:
    Texture _texture; // 纹理

public:
    Sprite() = default;
    virtual ~Sprite() = default;

    static Sprite* createAndAffiliate(ObjectScreen* parent, const std::string& texture_path, const glm::vec2& scale = glm::vec2(1.0f), Anchor anchor = Anchor::CENTER);

    virtual void render() override;

    virtual void setTexture(const Texture& texture);
    const Texture& getTexture() const { return _texture; }
    virtual glm::vec2 getOffset() override;

};