#include "abstract_button.h"
#include "game.h"

void AbstractButton::checkButtonState()
{
    glm::vec2 mouse_position = Game::getInstance().getMousePosition();
    _is_hovered = ifMouseInButtonArea(mouse_position);
        
    SDL_MouseButtonFlags mouse_button_state = Game::getInstance().getMouseButtonState();
    bool is_button_matched = (mouse_button_state & _matching_button);
    _is_pressed = (_is_pressed ? is_button_matched : (_is_hovered && is_button_matched));
}
