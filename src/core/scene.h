#pragma once

#include "object.h"
#include "object_world.h"
#include "camera.h"

class Scene : public Object
{
protected:
    glm::vec2 _world_size = glm::vec2(0); // 世界大小
    Camera _camera; // 摄像机
    std::vector<ObjectScreen*> _children_screen;
    std::vector<ObjectWorld*> _children_world;
    bool _is_paused = false; // 场景是否暂停
    bool _need_camera_dirty = false; // 是否在下一帧设置摄像机脏
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void init() override;
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    // 仅从列表中删除
    virtual void removeChild(Object* child) override;

    void pause() { _is_paused = true; }
    void resume() { _is_paused = false; }

    Camera& getCamera() { return _camera; }
    void toSetCameraDirty() { _need_camera_dirty = true; }

};