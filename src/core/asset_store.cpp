#include "asset_store.h"

AssetStore::~AssetStore()
{
    for (auto &pair : _textures) {
        SDL_DestroyTexture(pair.second);
    }
    _textures.clear();
    for (auto &pair : _sounds) {
        Mix_FreeChunk(pair.second);
    }
    _sounds.clear();
    for (auto &pair : _music) {
        Mix_FreeMusic(pair.second);
    }
    _music.clear();
    for (auto &pair : _fonts) {
        TTF_CloseFont(pair.second);
    }
    _fonts.clear();
}

void AssetStore::loadTexture(const std::string &file_path)
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer, file_path.c_str());
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s\n", file_path.c_str());
        return;
    }
    _textures.emplace(file_path, texture); // 如果已经存在，则不会插入
}

void AssetStore::loadSound(const std::string &file_path)
{
    Mix_Chunk *sound = Mix_LoadWAV(file_path.c_str());
    if (sound == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load sound: %s\n", file_path.c_str());
        return;
    }
    _sounds.emplace(file_path, sound); // 如果已经存在，则不会插入
}

void AssetStore::loadMusic(const std::string &file_path)
{
    Mix_Music *music = Mix_LoadMUS(file_path.c_str());
    if (music == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s\n", file_path.c_str());
        return;
    }
    _music.emplace(file_path, music); // 如果已经存在，则不会插入
}

void AssetStore::loadFont(const std::string &file_path, int file_size)
{
    TTF_Font *font = TTF_OpenFont(file_path.c_str(), static_cast<float>(file_size));
    if (font == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s\n", file_path.c_str());
        return;
    }
    _fonts.emplace(file_path + std::to_string(file_size), font); // 如果已经存在，则不会插入
}

SDL_Texture *AssetStore::getTexture(const std::string &file_path)
{
    auto iter = _textures.find(file_path);
    if (iter == _textures.end()) {
        loadTexture(file_path);
        iter = _textures.find(file_path);
    }
    if (iter == _textures.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to find texture: %s\n", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

Mix_Chunk *AssetStore::getSound(const std::string &file_path)
{
    auto iter = _sounds.find(file_path);
    if (iter == _sounds.end()) {
        loadSound(file_path);
        iter = _sounds.find(file_path);
    }
    if (iter == _sounds.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to find sound: %s\n", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

Mix_Music *AssetStore::getMusic(const std::string &file_path)
{
    auto iter = _music.find(file_path);
    if (iter == _music.end()) {
        loadMusic(file_path);
        iter = _music.find(file_path);
    }
    if (iter == _music.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to find music: %s\n", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}

TTF_Font *AssetStore::getFont(const std::string &file_path, int file_size)
{
    std::string key = file_path + std::to_string(file_size);
    auto iter = _fonts.find(key);
    if (iter == _fonts.end()) {
        loadFont(file_path, file_size);
        iter = _fonts.find(key);
    }
    if (iter == _fonts.end()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to find font: %s\n", file_path.c_str());
        return nullptr;
    }
    return iter->second;
}