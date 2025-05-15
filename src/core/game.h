#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <string>
#include <random>
#include "asset_store.h"

class Scene;
class Game
{
    AssetStore* _asset_store = nullptr; // 资源管理器

    glm::vec2 _resolution = glm::vec2(0); // 逻辑分辨率
    glm::vec2 _mouse_position = glm::vec2(0); // 鼠标位置
    SDL_MouseButtonFlags _mouse_button_state = SDL_BUTTON_LEFT; // 鼠标按键状态
    bool _is_running = true; // 游戏是否正在运行
    Scene* _current_scene = nullptr; // 当前场景
    Scene* _next_scene = nullptr; // 下一个场景

    Uint64 _FPS = 60; // 游戏帧率
    Uint64 _frame_delay = 0; // 帧延迟，单位ns
    float _dt = 0.0f; // 帧间隔

    SDL_Window* _window = nullptr; // 游戏窗口
    SDL_Renderer* _renderer = nullptr; // 渲染器
    TTF_TextEngine* _ttf_engine = nullptr; // 字体引擎

    std::mt19937 _gen = std::mt19937(std::random_device{}()); // 随机数生成器
public:
    void init(std::string title, int width, int height);    
    void run(Scene* scene);
    void handleEvents(); // 处理事件
    void update(float dt); // 更新游戏状态
    void render(); // 渲染游戏
    ~Game();

    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    Scene* getCurrentScene() { return _current_scene; }
    void setNextScene(Scene* scene) { _next_scene = scene; }

    glm::vec2 getResolution() const { return _resolution; }
    AssetStore* getAssetStore() { return _asset_store; }

    SDL_Renderer* getRenderer() { return _renderer; }
    TTF_TextEngine* getTTF_Engine() { return _ttf_engine; }

    glm::vec2 getMousePosition() const { return _mouse_position; }
    SDL_MouseButtonFlags getMouseButtonState() const { return _mouse_button_state; }

private:
    // 私有构造函数
    Game() {}
    // 禁止拷贝构造函数与赋值操作符
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void changeScene(Scene* scene);
};