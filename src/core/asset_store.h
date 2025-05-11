#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class AssetStore
{
    SDL_Renderer* _renderer = nullptr;
    std::unordered_map<std::string, SDL_Texture *> _textures;
    std::unordered_map<std::string, Mix_Chunk *> _sounds;
    std::unordered_map<std::string, Mix_Music *> _music;
    std::unordered_map<std::string, TTF_Font *> _fonts;
public:
    AssetStore(SDL_Renderer* renderer) {_renderer = renderer;}
    ~AssetStore();

    // 4个加载函数

    void loadTexture(const std::string &file_path);
    void loadSound(const std::string &file_path);
    void loadMusic(const std::string &file_path);
    void loadFont(const std::string &file_path, int file_size);

    // 4个读取函数

    SDL_Texture *getTexture(const std::string &file_path);
    Mix_Chunk *getSound(const std::string &file_path);
    Mix_Music *getMusic(const std::string &file_path);
    TTF_Font *getFont(const std::string &file_path, int file_size);

};