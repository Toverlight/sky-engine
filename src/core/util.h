#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "game.h"

namespace Math {
    glm::vec2 rotateVec2(glm::vec2 v, float radians);
    float angleBetweenVec2s(glm::vec2 a, glm::vec2 b);
}

namespace Graphics {
    /// @brief 渲染纹理
    /// @param texture 纹理
    /// @param position 左上角位置
    /// @param renderer 渲染器
    void renderTexture(const Texture& texture, const glm::vec2& position, SDL_Renderer* renderer = Game::getInstance().getRenderer());
    // TODO: 添加更多渲染函数
    // 例如：渲染文本、渲染多边形等
    /*
    绘制文本
    */

    void renderLine(const glm::vec2& start, const glm::vec2& end, SDL_FColor color, float thickness, SDL_Renderer* renderer = Game::getInstance().getRenderer());
    void renderFilledPolygon(const std::vector<SDL_FPoint>& points, SDL_FColor color, SDL_Renderer* renderer = Game::getInstance().getRenderer());
    // 绘制多边形边框。要求顶点顺时针排列
    void renderPolygonOutline(const std::vector<SDL_FPoint>& points, SDL_FColor color, float thickness, SDL_Renderer* renderer = Game::getInstance().getRenderer());
}

namespace Audio {
    inline void playMusic(const std::string& music_path, bool loop = true) { Mix_PlayMusic(Game::getInstance().getAssetStore()->getMusic(music_path), loop ? -1 : 0); }; // 播放音乐
    inline void playSound(const std::string& sound_path) { Mix_PlayChannel(-1, Game::getInstance().getAssetStore()->getSound(sound_path), 0); }; // 播放音效
    inline void stopMusic() { Mix_HaltMusic(); } // 停止音乐
    inline void stopSound() { Mix_HaltChannel(-1); } // 停止音效
    inline void pauseMusic() { Mix_PauseMusic(); } // 暂停音乐
    inline void pauseSound() { Mix_Pause(-1); } // 暂停音效
    inline void resumeMusic() { Mix_ResumeMusic(); } // 恢复音乐
    inline void resumeSound() { Mix_Resume(-1); } // 恢复音效
}

namespace Text {
    TTF_Text* createTTF_Text(const std::string& text, const std::string& font_path, int font_size, TTF_TextEngine* ttf_engine = Game::getInstance().getTTF_Engine());
}