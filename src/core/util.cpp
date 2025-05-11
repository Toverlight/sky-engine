#include "util.h"

void Graphics::renderTexture(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, SDL_Renderer* renderer)
 {
    if (renderer == nullptr || texture.texture == nullptr) {
        return;
    }

    SDL_FRect src_rect;
    src_rect.x = texture.clip.x;
    src_rect.y = texture.clip.y;
    src_rect.w = texture.clip.w;
    src_rect.h = texture.clip.h;

    SDL_FRect dst_rect;
    dst_rect.x = position.x - size.x / 2;
    dst_rect.y = position.y - size.y / 2;
    dst_rect.w = size.x;
    dst_rect.h = size.y;

    SDL_RenderTextureRotated(renderer, texture.texture, &src_rect, &dst_rect, texture.angle, nullptr, texture.is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

glm::vec2 Math::rotateVec2(glm::vec2 v, float radians)
{
    float cos_theta = cosf(radians);
    float sin_theta = sinf(radians);
    return glm::vec2(
        v.x * cos_theta - v.y * sin_theta,
        v.x * sin_theta + v.y * cos_theta
    );
}
