//
// Created by colte on 10.02.2023.
//

#include "Element.h"
#include <raylib.h>

namespace l5 {
    Element::Element(int type, Vector2D pos, ColorSt color)
    : _type(type), _pos(pos), _color(color), _isSelected(false), _needRemoval(false), _nextElement(nullptr) {
        SetPointer();
    }

    Element::Element(Element &element)
    : _type(element._type), _pos(element._pos), _color(element._color), _isSelected(false), _needRemoval(false),
    _nextElement(nullptr) {
        SetPointer();
    }

    Element::Element(Element *element)
    : _type(element->_type), _pos(element->_pos), _color(element->_color), _isSelected(false), _needRemoval(false),
    _nextElement(nullptr) {
        SetPointer();
    }

    void Element::Update() {
        static Vector2 buffer;
        static Element* lastClickElement = nullptr;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if(!elementSelected && !_isSelected && CheckPosition({mouse.x, mouse.y})) {
                _isSelected = true;
                elementSelected = true;
                selectedElement = this;
                buffer = mouse;
                lastClickElement = this;
            }
            else if(_isSelected) {
                if(mouse.x >= WORKSPACE_X_ST && mouse.x <= WORKSPACE_X_END
                && mouse.y >= WORKSPACE_Y_ST && mouse.y <= WORKSPACE_Y_END) {
                    if(lastClickElement == this) buffer = {mouse.x - buffer.x, mouse.y - buffer.y};
                    else buffer = {mouse.x - _pos.x, mouse.y - _pos.y};
                    _pos.x += buffer.x;
                    _pos.y += buffer.y;
                }
                HandleElementSelection();
                lastClickElement = nullptr;
            }
        }
        if(IsKeyPressed(KEY_DELETE) && _isSelected) {
            StartRemoval();
            _isSelected = false;
            resetSelection = true;
            selectedElement = nullptr;
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

    void Element::HandleElementSelection(bool endSelection) {
        _isSelected = false;
        if(endSelection) HandleSelection();
    }

    void Element::HandleSelection() {
        resetSelection = true;
        selectedElement = nullptr;
    }

    void Element::SelectionActivate() {
        _isSelected = true;
    }

    void Element::ReplacePointer(Element *el, std::vector<Element *> &vec) {
        if(*vec.begin() != el) {
            auto iter = vec.begin();
            while ((*iter)->_nextElement != el) {
                iter++;
            }
            (*iter)->_nextElement = el->_nextElement;
            if(el->_nextElement == nullptr) lastElement = *iter;
        }
    }

    void Element::SetPointer() {
        if(lastElement) lastElement->_nextElement = this;
        lastElement = this;
    }
} // l5