#pragma once
#include <glm/glm.hpp>

class Scene;
struct Camera
{
    glm::vec2 position; // 摄像机位置
    float zoom; // 缩放比例
    float rotation; // 旋转角度
    
    bool is_dirty = false; // 是否为脏
    Scene* scene = nullptr; // 场景

    Camera() : position(0.0f, 0.0f), zoom(1.0f), rotation(0.0f) {}

    void setPosition(const glm::vec2& pos);

    void setZoom(float z);

    void setRotation(float r);

    // 通知场景摄像机已修改
    void informModificationToScene();
};
