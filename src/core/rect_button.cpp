#include "rect_button.h"

bool RectButton::ifMouseInButtonArea(const glm::vec2& mouse_position)
{
    glm::vec2 button_position = getPosScreen();
    return (mouse_position.x >= button_position.x - _size.x / 2 && mouse_position.x <= button_position.x + _size.x / 2 &&
            mouse_position.y >= button_position.y - _size.y / 2 && mouse_position.y <= button_position.y + _size.y / 2);
}
