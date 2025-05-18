#pragma once

#include "sprite.h"

class Animation : public Sprite
{
protected:
    int _current_frame = 0; // 当前帧
    int _total_frames = 0; // 总帧数
    int _fps = 10; // 帧率
    float _frame_duration = 0.0f; // 每帧持续时间
    float _elapsed_time = 0.0f; // 已经过的时间
    bool _is_looping = true; // 是否循环播放
    bool _is_playing = true; // 是否正在播放 TODO: play测试通过，但其它flag待测试
    bool _is_reversed = false; // 是否正在反向播放
    bool _is_reversible = false; // 是否到头反转
    bool _is_frame_duration_dirty = true; // 是否帧持续时间脏
    void (* _onAnimationEndCallback)() = nullptr; // 动画结束回调

public:
    Animation() = default;
    virtual ~Animation() = default;

    static Animation* createAndAffiliate(ObjectScreen* parent, const std::string& texture_path, const glm::vec2& scale = glm::vec2(1.0f), Anchor anchor = Anchor::CENTER);

    virtual void update(float dt) override;

    // 接受横向精灵图作为纹理
    virtual void setTexture(const Texture &texture) override;
    void setFPS(int fps);
    void setLooping(bool looping);
    void setPlaying(bool playing) { _is_playing = playing; }
    void setReversed(bool reversed) { _is_reversed = reversed; }
    void setReversible(bool reversible);
    void setCurrentFrame(int frame) { _current_frame = (frame < 0 ? 0 : (frame >= _total_frames ? _total_frames - 1 : frame)); }
    void setOnAnimationEndCallback(void (*callback)()) { _onAnimationEndCallback = callback; }

    float getFrameDuration();
    int getCurrentFrame() { return _current_frame; }

};