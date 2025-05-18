#include "animation.h"

Animation* Animation::createAndAffiliate(ObjectScreen* parent, const std::string& texture_path, const glm::vec2& scale, Anchor anchor)
{
    Animation* animation = new Animation();
    animation->init();
    animation->setParent(parent);
    animation->setTexture(Texture(texture_path));
    animation->setScale(scale);
    animation->setAnchor(anchor);
    if (parent) parent->toAddChild(animation);
    return animation;
}

void Animation::update(float dt)
{
    if (!_is_playing) return;

    _elapsed_time += dt;
    while (_elapsed_time >= getFrameDuration()) {
        _elapsed_time -= getFrameDuration();
        if (_is_reversed) {
            _current_frame--;
            if (_current_frame < 0) {
                if (_is_reversible) {
                    _current_frame = 0;
                    _is_reversed = false;
                } else if (_is_looping) {
                    _current_frame = _total_frames - 1;
                } else {
                    _is_playing = false;
                    if (_onAnimationEndCallback) _onAnimationEndCallback();
                }
            }
        } else {
            _current_frame++;
            if (_current_frame >= _total_frames) {
                if (_is_reversible) {
                    _current_frame = _total_frames - 1;
                    _is_reversed = true;
                } else if (_is_looping) {
                    _current_frame = 0;
                } else {
                    _is_playing = false;
                    if (_onAnimationEndCallback) _onAnimationEndCallback();
                }
            }
        }
    }
    _texture.clip.x = _current_frame * _texture.clip.w;
}

void Animation::setTexture(const Texture &texture)
{
    _texture = texture;
    _total_frames = static_cast<int>(_texture.clip.w / _texture.clip.h);
    _texture.clip.w = _texture.clip.h;
    _texture.size = glm::vec2(_texture.clip.w, _texture.clip.h);
    setSize(_texture.size);

}

void Animation::setFPS(int fps)
{
    if (fps <= 0) {
        fps = 1;
    }
    _fps = fps;
    _is_frame_duration_dirty = true;
}

void Animation::setLooping(bool looping)
{
    _is_looping = looping;
    if (_is_looping) _is_reversible = false;
}

void Animation::setReversible(bool reversible)
{
    _is_reversible = reversible;
    if (_is_reversible) _is_looping = false;
}

float Animation::getFrameDuration()
{
    if (_is_frame_duration_dirty) {
        _frame_duration = 1.0f / _fps;
        _is_frame_duration_dirty = false;
    }
    return _frame_duration;
}