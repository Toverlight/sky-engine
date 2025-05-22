#include "scene_init.h"
#include "../core/sprite.h"
#include "startup_config.h"
#include "../core/util.h"
#include "../core/text_label.h"
#include "../core/cursor_static.h"
#include "../core/animation.h"
#include "../core/sprite_button.h"
#include <SDL3/SDL_mouse.h>

void SceneInit::init()
{
    Scene::init();
    StartupConfig& config = StartupConfig::getInstance();

    ObjectScreen* test_show = new ObjectScreen();
    test_show->init();
    test_show->setPosScreen(glm::vec2(config.window_width / 2, config.window_height / 2));
    toAddChild(test_show);
    Sprite::createAndAffiliate(test_show, "assets/test/koisi.png", glm::vec2(0.7f));

    ObjectScreen* test_text = new ObjectScreen();
    test_text->init();
    test_text->setPosScreen(glm::vec2(610, 80));
    toAddChild(test_text);
    TextLabel::createAndAffiliate(test_text, "Hello Colorful World!", "assets/test/fonts/ALGER.TTF", 50, { 0.1f, 0.7f, 0.3f, 1.0f }, Anchor::BOTTOM_CENTER);
    TextLabel::createAndAffiliate(test_text, "Hello Consolas World(", "assets/test/fonts/CONSOLA.TTF", 40, { 0.2f, 0.3f, 0.8f, 1.0f }, Anchor::TOP_CENTER);

    ObjectScreen* test_text2 = new ObjectScreen();
    test_text2->init();
    test_text2->setPosScreen(glm::vec2(610, 150));
    toAddChild(test_text2);
    TextLabel::createAndAffiliate(test_text2, "请输入文本", "assets/test/fonts/SIMYOU.TTF", 40, { 0.5f, 0.5f, 0.5f, 1.0f }, Anchor::CENTER);

    SpriteButton* test_sprite_button = SpriteButton::create("assets/test/UI/A_Start1.png", "assets/test/UI/A_Start2.png", "assets/test/UI/A_Start3.png", glm::vec2(192, 64));
    test_sprite_button->setPosScreen(glm::vec2(1000, 100));
    test_sprite_button->setOnHoverCallback([]() {
        SDL_Log("Button hovered!\n");
    });
    test_sprite_button->setOnClickCallback([]() {
        SDL_Log("Button clicked!\n");
    });
    toAddChild(test_sprite_button);

    ObjectScreen* test_animation = new ObjectScreen();
    test_animation->init();
    test_animation->setPosScreen(glm::vec2(800, 150));
    toAddChild(test_animation);
    Animation::createAndAffiliate(test_animation, "assets/test/sprite/ghost-Sheet.png", glm::vec2(2.0f));

    CursorStatic* cursor = new CursorStatic("assets/test/UI/pointer_c_shaded.png");
    cursor->init();
    cursor->setCursorScale(glm::vec2(1.5f));
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
    Graphics::renderFilledPolygon({{0, 0}, {300, 100}, {300, 300}, {0, 300}}, {0, 1, 0, 1});
    Graphics::renderLine({0, 0}, {300, 300}, {1, 0, 0, 1}, 5);
    Graphics::renderPolygonOutline({{50, 480}, {800, 560}, {900, 700}, {500, 700}}, {0, 0, 1, 1}, 5);
    Scene::render();
}
