#include "startup_config.h"
#include <fstream>
#include <json.hpp>

bool loadStartupConfig(StartupConfig &config)
{
    try {
        std::ifstream in("src/config/startup.json");
        if (!in.is_open()) {
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
        return false;
    }
}
