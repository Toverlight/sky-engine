#include "game.h"
#include "scene.h"
void Game::run(Scene* scene)
{
    if (!scene) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot run game without a scene!\n");
        return;
    }
    _current_scene = scene;
    while (_is_running) {
        auto start = SDL_GetTicksNS();
        if (_next_scene) {
            changeScene(_next_scene);
            _next_scene = nullptr;
        }
        handleEvents();
        update(_dt);
        render();
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < _frame_delay) {
            SDL_DelayNS(_frame_delay - elapsed);
            _dt = static_cast<float>(_frame_delay / 1.0e9);
        } else {
            _dt = static_cast<float>(elapsed / 1.0e9);
        }
        // SDL_Log("FPS: %f", 1.0f / _dt);
    }
}

void Game::handleEvents()
{
    // 获取鼠标位置
    _mouse_button_state = SDL_GetMouseState(&_mouse_position.x, &_mouse_position.y);
    // 限制比例，不出现黑边的做法
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    SDL_SetWindowAspectRatio(_window, _resolution.x / _resolution.y, _resolution.x / _resolution.y);
    _mouse_position *= _resolution / glm::vec2(w, h);
    // 处理事件
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                _is_running = false;
                break;
            default:
                _current_scene->handleEvents(event);
                break;
        }
    }
}

void Game::update(float dt)
{
    _current_scene->update(dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    _current_scene->render();
    SDL_RenderPresent(_renderer);
}

Game::~Game()
{
     if (_current_scene) {
        delete _current_scene;
    }
    if (_asset_store) {
        delete _asset_store;
    }
    // 释放渲染器和窗口
    if (_ttf_engine) {
        TTF_DestroyRendererTextEngine(_ttf_engine);
    }
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window) {
        SDL_DestroyWindow(_window);
    }
    // 退出Mix
    Mix_CloseAudio();
    Mix_Quit();
    // 退出TTF
    TTF_Quit();
    // 退出SDL
    SDL_Quit();

}

void Game::changeScene(Scene *scene)
{
    if (_current_scene) {
        delete _current_scene;
    }
    _current_scene = scene;
    if (_current_scene) {
        _current_scene->init();
    }
}

void Game::init(std::string title, int width, int height)
{
    _resolution = glm::vec2(width, height);
    // SDL3初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_初始化失败: %s\n", SDL_GetError());
    }
    // 不需要进行SDL_image的初始化
    // SDL3_Mixer的初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }
    if (!Mix_OpenAudio(0, NULL)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer打开音频失败: %s\n", SDL_GetError());
    }
    Mix_AllocateChannels(16); // 设置音频通道数16
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4); // 设置音效音量
    // SDL3_TTF的初始化
    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF初始化失败: %s\n", SDL_GetError());
    }
    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &_window, &_renderer);
    if (!_window || !_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL创建窗口或渲染器失败: %s\n", SDL_GetError());
    }
    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    _ttf_engine = TTF_CreateRendererTextEngine(_renderer);

    // 计算帧延迟
    _frame_delay = 1000000000 / _FPS;

    // 创建资源管理器
    _asset_store = new AssetStore(_renderer);

}
