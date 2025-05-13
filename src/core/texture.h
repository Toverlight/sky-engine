#pragma once
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <string>

struct Texture
{
    SDL_Texture* texture = nullptr; // 纹理
    glm::vec2 size = glm::vec2(0); // 纹理大小
    glm::vec2 center = glm::vec2(0); // 纹理中心//TODO: center功能
    float angle = 0.0f; // 旋转角度
    SDL_FRect clip = { 0, 0, 0, 0 }; // 裁剪区域
    bool is_flipped = false; // 是否翻转

    Texture() = default;
    Texture(const std::string& path);
};