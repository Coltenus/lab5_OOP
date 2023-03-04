//
// Created by colte on 10.02.2023.
//

#include "Element.h"
#include <raylib.h>
#include "../ElementIterator.h"

namespace l5 {
    Element::Element(int type, Vector2D pos, ColorSt color)
    : _type(type), _pos(pos), _color(color), _isSelected(false), _needRemoval(false), _nextElement(nullptr),
    _previousElement(nullptr) {
    }

    Element::Element(Element &element)
    : _type(element._type), _pos(element._pos), _color(element._color), _isSelected(false), _needRemoval(false),
    _nextElement(element._nextElement), _previousElement(element._nextElement) {
    }

    Element::Element(Element *element)
    : _type(element->_type), _pos(element->_pos), _color(element->_color), _isSelected(false), _needRemoval(false),
    _nextElement(element->_nextElement), _previousElement(element->_nextElement) {
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
                ElementIterator::resetValues = true;
            }
        }
        if(IsKeyPressed(KEY_DELETE) && _isSelected) {
            StartRemoval();
            _isSelected = false;
            resetSelection = true;
            selectedElement = nullptr;
            ElementIterator::resetValues = true;
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
        if(*vec.begin() != el && vec.begin()+1 != vec.end()) {
            auto previous = el->_previousElement;
            if(previous) previous->_nextElement = el->_nextElement;
            if(el->_nextElement) el->_nextElement->_previousElement = previous;
            if(el->_nextElement == nullptr) lastElement = previous;
        }
    }

    void Element::InsertPointer(std::vector<Element *> &vec, int pos) {
        if(vec.size() > 1 && pos < vec.size() && pos >= 0) {
            if(pos > 0) {
                if(pos < vec.size()-1)
                    (*(vec.begin()+pos-1))->_nextElement = (*(vec.begin()+pos+1));
                else (*(vec.begin()+pos-1))->_nextElement = nullptr;
            }
            if(pos < vec.size()-1) {
                if(pos-1 >= 0)
                    (*(vec.begin()+pos+1))->_previousElement = (*(vec.begin()+pos-1));
                else (*(vec.begin()+pos+1))->_previousElement = nullptr;
            }
        }
    }

    void Element::SetPointer() {
        _previousElement = lastElement;
        if(lastElement) lastElement->_nextElement = this;
        lastElement = this;
        _nextElement = nullptr;
    }

    bool Element::operator==(Element *element) {
        return _pos.x == element->_pos.x
        && _pos.y == element->_pos.y
        && (_nextElement == element->_nextElement
            || _previousElement == element->_previousElement);
    }

    Element& Element::operator=(Element *element) {
        _pos = element->_pos;
        _nextElement = element->_nextElement;
        _previousElement = element->_previousElement;
        return *this;
    }

    bool Element::IsSame(Element* element) {
        bool result = true;
        if(_previousElement) result = _previousElement->_nextElement == element;
        if(_nextElement) result = result && _nextElement->_previousElement == element;
        return result;
    }

    std::string Element::GetTextData(Vector2D* pos, bool needPos, bool needColor) {
        std::string result;
        static char buffer[20];
        snprintf(buffer, 20, "type=%d ", _type);
        result += buffer;
        if(needPos) {
            if(pos)
                snprintf(buffer, 20, "pos=%d,%d ", (int)pos->x - WORKSPACE_X_ST, (int)pos->y - WORKSPACE_Y_ST);
            else snprintf(buffer, 20, "pos=%d,%d ", (int)_pos.x - WORKSPACE_X_ST, (int)_pos.y - WORKSPACE_Y_ST);
            result += buffer;
        }
        if(needColor) {
            snprintf(buffer, 20, "color=%02X%02X%02X ", _color.r, _color.g, _color.b);
            result += buffer;
        }
        return result;
    }
} // l5