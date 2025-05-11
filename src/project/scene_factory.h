#pragma once
#include <string>
#include "../core/scene.h"
// 这里包含所有场景的头文件
#include "scene_init.h"
// ---

// 场景工厂类
// 把有的场景都写进来
class SceneFactory
{
public:
    static Scene* createScene(const std::string& sceneName);
};