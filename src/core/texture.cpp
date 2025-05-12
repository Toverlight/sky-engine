#include "texture.h"
#include "asset_store.h"
#include "game.h"

Texture::Texture(const std::string &path)
{
    texture = Game::getInstance().getAssetStore()->getTexture(path);
    if (texture) {
        SDL_GetTextureSize(texture, &clip.w, &clip.h);
    }
    else {
        SDL_Log("Failed to load texture: %s\n", path.c_str());
    }
}