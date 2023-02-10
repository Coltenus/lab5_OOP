//
// Created by colte on 10.02.2023.
//

#include "Element.h"
#include "../libs/imgui/imgui_setup.h"

namespace l5 {
    Element::Element(Vector2D pos, Color color)
    : _pos(pos), _color(color), _isSelected(false) {}

    void Element::Update() {
        if(!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if(!elementSelected && !_isSelected && CheckPosition({mouse.x, mouse.y})) {
                _isSelected = true;
                elementSelected = true;
            }
            else if(_isSelected) {
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