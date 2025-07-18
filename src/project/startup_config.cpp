#include "startup_config.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

bool loadStartupConfig(StartupConfig &config)
{
    try {
        // 获取可执行文件路径（编译器相关）
        fs::path exePath = fs::current_path(); // 当前工作目录
        std::cerr << "Current working directory: " << exePath << std::endl;
        fs::path configPath = exePath / "config" / "project" / "startup.json";

        std::ifstream in(configPath);
        if (!in.is_open()) {
            std::cerr << "Failed to open startup.json file." << std::endl;
            return false;
        }
        nlohmann::json j;
        in >> j;

        config.title = j.value("title", "My Game");
        config.startup_scene = j.value("startup_scene", "SceneInit");
        config.window_width = j.value("window_width", 1280);
        config.window_height = j.value("window_height", 720);
        config.fullscreen = j.value("fullscreen", false);
        config.mode = j.value("mode", "debug");
        config.asset_path = j.value("asset_path", "assets/");

        in.close();

        return true;
    } catch (...) {
        std::cerr << "Error loading startup configuration." << std::endl;
        return false;
    }
}
