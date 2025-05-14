#include "../core/game.h"
#include "startup_config.h"
#include "scene_factory.h"

int main()
{
    StartupConfig& config = StartupConfig::getInstance();
    if (!loadStartupConfig(config)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load startup.json!\n");
        return -1;
    }

    Game::getInstance().init(config.title, config.window_width, config.window_height);

    auto* scene = SceneFactory::createScene(config.startup_scene);
    if (!scene) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot create scene: %s\n", config.startup_scene.c_str());
        return -1;
    }

    Game::getInstance().run(scene);

    return 0;
}