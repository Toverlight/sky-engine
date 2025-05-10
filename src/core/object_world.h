#pragma once
#include "object_screen.h"

class ObjectWorld : public ObjectScreen
{
protected:
    glm::vec2 _pos_world = glm::vec2(0); // 世界坐标
public:
    ObjectWorld() = default;
    virtual ~ObjectWorld() = default;

    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;

    virtual glm::vec2 getPosScreen() override;
    virtual void setPosScreen(const glm::vec2& pos) override;
    glm::vec2 getPosWorld();
    void setPosWorld(const glm::vec2& pos);
private:
    bool _is_pos_world_dirty = false; // 世界坐标是否脏
    bool _is_pos_screen_dirty = false; // 屏幕坐标是否脏
};