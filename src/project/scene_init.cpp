#include "scene_init.h"
#include "../core/sprite.h"
#include "startup_config.h"
#include "../core/util.h"
#include "../core/rect_button.h"
#include "../core/text_label.h"
#include "../core/cursor_static.h"
#include <SDL3/SDL_mouse.h>

void SceneInit::init()
{
    Scene::init();
    StartupConfig& config = StartupConfig::getInstance();

    ObjectScreen* test_show = new ObjectScreen();
    test_show->init();
    test_show->setPosScreen(glm::vec2(config.window_width / 2, config.window_height / 2));
    toAddChild(test_show);
    auto sprite = Sprite::createAndAffiliate(test_show, "assets/test/koisi.png");
    sprite->setScale(glm::vec2(1.0f));

    ObjectScreen* test_text = new ObjectScreen();
    test_text->init();
    test_text->setPosScreen(glm::vec2(550, 80));
    toAddChild(test_text);
    TextLabel::createAndAffiliate(test_text, "Hello World!", "assets/test/fonts/ALGER.TTF", 40);

    RectButton* test_button1 = new RectButton();
    test_button1->init();
    test_button1->setPosScreen(glm::vec2(config.window_width - 200, config.window_height / 2 + 100));
    test_button1->setSize(glm::vec2(200, 100));
    test_button1->setOnHoverCallback([]() {
        SDL_Log("【1】Hovered!\n");
    });
    test_button1->setOnClickCallback([]() {
        SDL_Log("【1】Clicked!\n");
    });
    toAddChild(test_button1);

    RectButton* test_button2 = new RectButton();
    test_button2->init();
    test_button2->setPosScreen(glm::vec2(config.window_width - 200, config.window_height / 2 + 250));
    test_button2->setSize(glm::vec2(200, 100));
    test_button2->setOnHoverCallback([]() {
        SDL_Log("【2】Hovered!\n");
    });
    test_button2->setOnClickCallback([]() {
        SDL_Log("【2】Clicked!\n");
    });
    toAddChild(test_button2);

    CursorStatic* cursor = new CursorStatic("assets/test/cursor/leaf_cursor.png");
    cursor->init();
    cursor->setCursorScale(glm::vec2(2.0f));
    toAddChild(cursor);
    
    SDL_HideCursor();

    SDL_Log("SceneInit initialized.\n");
}

bool SceneInit::handleEvents(SDL_Event &event)
{
    return Scene::handleEvents(event);
}

void SceneInit::update(float dt)
{
    Scene::update(dt);
}

void SceneInit::render()
{
    Scene::render();
    Graphics::renderFilledPolygon({{0, 0}, {300, 100}, {300, 300}, {0, 300}}, {0, 1, 0, 1});
    Graphics::renderLine({0, 0}, {300, 300}, {1, 0, 0, 1}, 5);
    Graphics::renderPolygonOutline({{50, 480}, {800, 560}, {900, 700}, {500, 700}}, {0, 0, 1, 1}, 5);
}
