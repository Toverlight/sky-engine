#pragma once
#include <SDL3/SDL.h>
#include <vector>

class Object
{
protected:
    bool _is_active = true; // 是否需要处理逻辑
    bool _need_remove = false; // 是否在下一帧删除
    std::vector<Object*> _to_be_added; // 下一帧将加入的子对象
    std::vector<Object*> _children; // 子对象列表

    
public:
    Object() = default;
    virtual ~Object();

    virtual void init();
    virtual bool handleEvents(SDL_Event& event);
    virtual void update(float dt);
    virtual void render();
    
    bool isActive() const { return _is_active; }
    void setActive(bool active) { _is_active = active; }
    void toRemove() { _need_remove = true; }

    virtual void toAddChild(Object* child) { _to_be_added.push_back(child); }
    virtual void removeChild(Object* child) { _children.erase(std::remove(_children.begin(), _children.end(), child), _children.end()); }

};