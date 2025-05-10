#pragma once
#include <glm/glm.hpp>

struct Camera
{
    glm::vec2 position; // 摄像机位置
    float zoom; // 缩放比例
    float rotation; // 旋转角度

    Camera() : position(0.0f, 0.0f), zoom(1.0f), rotation(0.0f) {}
};
