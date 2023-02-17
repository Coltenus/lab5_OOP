//
// Created by colte on 10.02.2023.
//

#include "Element.h"
#include <raylib.h>

namespace l5 {
    Element::Element(int type, Vector2D pos, ColorSt color)
    : _type(type), _pos(pos), _color(color), _isSelected(false), _needRemoval(false) {}

    Element::Element(Element &element)
    : _type(element._type), _pos(element._pos), _color(element._color), _isSelected(false), _needRemoval(false) {}

    Element::Element(Element *element)
    : _type(element->_type), _pos(element->_pos), _color(element->_color), _isSelected(false), _needRemoval(false) {}

    void Element::Update() {
        static Vector2 buffer;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if(!elementSelected && !_isSelected && CheckPosition({mouse.x, mouse.y})) {
                _isSelected = true;
                elementSelected = true;
                buffer = mouse;
            }
            else if(_isSelected) {
                if(mouse.x >= WORKSPACE_X_ST && mouse.x <= WORKSPACE_X_END
                && mouse.y >= WORKSPACE_Y_ST && mouse.y <= WORKSPACE_Y_END) {
                    buffer = {mouse.x - buffer.x, mouse.y - buffer.y};
                    _pos.x += buffer.x;
                    _pos.y += buffer.y;
                }
                _isSelected = false;
                resetSelection = true;
            }
        }
        if(IsKeyPressed(KEY_DELETE) && _isSelected) {
            StartRemoval();
            _isSelected = false;
            resetSelection = true;
        }
    }

    Vector2D Element::GetPos() {
        return _pos;
    }

    void Element::SetPos(Vector2D pos) {
        _pos = pos;
    }

    void Element::StartRemoval() {
        _needRemoval = true;
    }

    bool Element::NeedRemoval() {
        return _needRemoval;
    }

    int Element::GetType() {
        return _type;
    }

    unsigned char *Element::GetRedP() {
        return &_color.r;
    }

    unsigned char *Element::GetGreenP() {
        return &_color.g;
    }

    unsigned char *Element::GetBlueP() {
        return &_color.b;
    }
} // l5