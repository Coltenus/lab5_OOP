//
// Created by colte on 10.02.2023.
//

#include "Element.h"
#include <raylib.h>

namespace l5 {
    Element::Element(Vector2D pos, ColorSt color)
    : _pos(pos), _color(color), _isSelected(false) {}

    void Element::Update() {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if(!elementSelected && !_isSelected && CheckPosition({mouse.x, mouse.y})) {
                _isSelected = true;
                elementSelected = true;
            }
            else if(_isSelected) {
                if(mouse.x >= WORKSPACE_X_ST && mouse.x <= WORKSPACE_X_END
                && mouse.y >= WORKSPACE_Y_ST && mouse.y <= WORKSPACE_Y_END)
                    _pos = {mouse.x, mouse.y};
                _isSelected = false;
                resetSelection = true;
            }
        }
    }

    Vector2D Element::GetPos() {
        return _pos;
    }
} // l5