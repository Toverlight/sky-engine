#pragma once
#include <string>
#include "object_screen.h"
#include "sprite.h"

class CursorStatic : public ObjectScreen
{
protected:
    Sprite* _cursor_sprite_weak = nullptr; // 注：_weak:弱指针，不负责生命周期

public:
    CursorStatic() = default;
    CursorStatic(Sprite* cursor_sprite): _cursor_sprite_weak(cursor_sprite) {}
    CursorStatic(const std::string& cursor_img_path);
    virtual ~CursorStatic() = default;

    virtual void update(float dt) override;

    void setCursorSprite(Sprite* cursor_sprite) { _cursor_sprite_weak = cursor_sprite; }

    virtual void setCursorSize(const glm::vec2& size) { if (_cursor_sprite_weak) _cursor_sprite_weak->setSize(size); }
    virtual void setCursorScale(const glm::vec2& scale) { if (_cursor_sprite_weak) _cursor_sprite_weak->setScale(scale); }

private:
    void syncCursorPosition();

};