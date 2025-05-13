#pragma once
#include <string>

struct StartupConfig
{
    std::string title = "My Game"; // 窗口标题
    std::string startup_scene = "SceneInit"; // 启动场景。与SceneFactory::createScene()中的场景名称一致
    int window_width = 1280; // 窗口宽度
    int window_height = 720; // 窗口高度
    bool fullscreen = false; // 是否全屏
    std::string mode = "debug"; // 模式
    std::string asset_path = "assets/"; // 资源路径

    static StartupConfig& getInstance()
    {
        static StartupConfig instance;
        return instance;
    }
    
private:
    StartupConfig() = default;
    StartupConfig(const StartupConfig&) = delete;
    StartupConfig& operator=(const StartupConfig&) = delete;

};

// 加载startup.json配置文件并解析
bool loadStartupConfig(StartupConfig& config);