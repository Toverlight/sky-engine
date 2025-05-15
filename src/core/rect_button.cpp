#include "rect_button.h"
#include "util.h"

bool RectButton::ifMouseInButtonArea(const glm::vec2& mouse_position)
{
    glm::vec2 button_position = getPosScreen();
    return (mouse_position.x >= button_position.x - _size.x / 2 && mouse_position.x <= button_position.x + _size.x / 2 &&
            mouse_position.y >= button_position.y - _size.y / 2 && mouse_position.y <= button_position.y + _size.y / 2);
}

void RectButton::render()
{
    // 测试代码
    // TODO 删去测试代码
    SDL_FColor color = { 0.0f, 0.0f, 1.0f, 1.0f };
    if (_is_pressed) {
        color = { 1.0f, 0.0f, 0.0f, 1.0f };
    } else if (_is_hovered) {
        color = { 0.0f, 1.0f, 0.0f, 1.0f };
    }

    Graphics::renderFilledPolygon({
        { getPosScreen().x - _size.x / 2, getPosScreen().y - _size.y / 2 },
        { getPosScreen().x + _size.x / 2, getPosScreen().y - _size.y / 2 },
        { getPosScreen().x + _size.x / 2, getPosScreen().y + _size.y / 2 },
        { getPosScreen().x - _size.x / 2, getPosScreen().y + _size.y / 2 }
    }, color);

}
