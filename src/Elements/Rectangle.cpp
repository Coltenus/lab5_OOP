//
// Created by colte on 10.02.2023.
//

#include "Rectangle.h"
#include <raylib.h>

namespace l5 {
    Rectangle::Rectangle(Vector2D pos, Vector2D size, ColorSt color, int thickness)
    : Element(2, pos, color), _size(size) {
        int buf = _size.x;
        if(buf > size.y)
            buf = size.y;
        if(thickness > buf)
            _thickness = buf;
        else _thickness = thickness;
    }

    Rectangle::Rectangle(Vector2D pos, Vector2D size, ColorSt color)
    : Rectangle(pos, size, color, 1) {}

    Rectangle::Rectangle(Rectangle &rectangle)
    : Element(rectangle), _size(rectangle._size), _thickness(rectangle._thickness) {}

    Rectangle::Rectangle(Rectangle *rectangle)
    : Element(rectangle), _size(rectangle->_size), _thickness(rectangle->_thickness) {}

    void Rectangle::Draw(Vector2D* pos) {
        if(_isSelected) _color.a = 120;
        else _color.a = 255;
        if(pos == nullptr)
            DrawRectangleLinesEx({_pos.x - _size.x, _pos.y - _size.y, _size.x*2, _size.y*2}, _thickness, {_color.r, _color.g, _color.b, _color.a});
        else DrawRectangleLinesEx({pos->x - _size.x, pos->y - _size.y, _size.x*2, _size.y*2}, _thickness, {_color.r, _color.g, _color.b, _color.a});
    }

    bool Rectangle::CheckPosition(Vector2D mouse, Vector2D* pos) {
        bool result;
        if(pos) result = mouse.x >= pos->x - _size.x && mouse.x <= pos->x + _size.x
                && mouse.y >= pos->y - _size.y && mouse.y <= pos->y + _size.y;
        else result = mouse.x >= _pos.x - _size.x && mouse.x <= _pos.x + _size.x
                && mouse.y >= _pos.y - _size.y && mouse.y <= _pos.y + _size.y;
        return result;
    }

    bool Rectangle::CheckPosition(Vector2D pos1, Vector2D pos2) {
        bool resultX, resultY;
        if(pos1.x <= pos2.x)
            resultX = _pos.x + _size.x >= pos1.x && _pos.x - _size.x <= pos2.x;
        else resultX = _pos.x + _size.x >= pos2.x && _pos.x - _size.x <= pos1.x;
        if(pos1.y <= pos2.y)
            resultY = _pos.y + _size.y >= pos1.y && _pos.y - _size.y <= pos2.y;
        else resultY = _pos.y + _size.y >= pos2.y && _pos.y - _size.y <= pos1.y;
        return resultX && resultY;
    }

    float *Rectangle::GetSizeXP() {
        return &_size.x;
    }

    float *Rectangle::GetSizeYP() {
        return &_size.y;
    }

    int *Rectangle::GetThickness() {
        return &_thickness;
    }

    bool Rectangle::operator==(Element *element) {
        return Element::operator==(element)
        && _size.x == reinterpret_cast<Rectangle*>(element)->_size.x
        && _size.y == reinterpret_cast<Rectangle*>(element)->_size.y
        && _thickness == reinterpret_cast<Rectangle*>(element)->_thickness;
    }

    Rectangle &Rectangle::operator=(Element *element) {
        Element::operator=(element);
        _size = reinterpret_cast<Rectangle*>(element)->_size;
        _thickness = reinterpret_cast<Rectangle*>(element)->_thickness;
        return *this;
    }
} // l5