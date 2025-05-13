#pragma once
#include <glm/glm.hpp>

class Scene;
class Camera
{
protected:
    glm::vec2 position; // 摄像机位置
    float zoom; // 缩放比例
    float rotation; // 旋转角度
    
    bool is_dirty = false; // 是否为脏
    Scene* scene = nullptr; // 场景

public:
    Camera() : position(0.0f, 0.0f), zoom(1.0f), rotation(0.0f) {}
    Camera(Scene* scene): position(0.0f, 0.0f), zoom(1.0f), rotation(0.0f), scene(scene) {}

    void setPosition(const glm::vec2& pos);
    glm::vec2 getPosition() const { return position; }
    
    void setZoom(float z);
    float getZoom() const { return zoom; }

    void setRotation(float r);
    float getRotation() const { return rotation; }

    void setScene(Scene* s) { scene = s; }
    Scene* getScene() { return scene; }

    void setDirty(bool dirty) { is_dirty = dirty; }
    bool isDirty() const { return is_dirty; }

private:
    // 通知场景摄像机已修改
    void informModificationToScene();
};
