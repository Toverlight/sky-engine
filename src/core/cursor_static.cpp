#include "cursor_static.h"
#include "def.h"
#include "game.h"

CursorStatic::CursorStatic(const std::string& cursor_img_path)
{
    _cursor_sprite = Sprite::createAndAffiliate(this, cursor_img_path, glm::vec2(1.0f), Anchor::TOP_LEFT);
    if (!_cursor_sprite)
    {
        SDL_Log("Failed to create cursor sprite from path: %s", cursor_img_path.c_str());
    }
}

void CursorStatic::update(float dt)
{
    syncCursorPosition();   
    ObjectScreen::update(dt);
}

void CursorStatic::syncCursorPosition()
{
    if (_cursor_sprite)
    {
        auto cursor_pos = Game::getInstance().getMousePosition();
        setPosScreen(cursor_pos);
    }
}