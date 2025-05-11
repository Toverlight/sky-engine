#pragma once
#include <glm/glm.hpp>
#include "texture.h"
#include "game.h"

namespace Math {
    glm::vec2 rotateVec2(glm::vec2 v, float radians);
}

namespace Graphics {
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, SDL_Renderer* renderer = Game::getInstance().getRenderer());
    // TODO: 添加更多渲染函数
    // 例如：渲染文本、渲染多边形等
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