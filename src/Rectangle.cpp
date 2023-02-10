//
// Created by colte on 10.02.2023.
//

#include "Rectangle.h"
#include <raylib.h>

namespace l5 {
    Rectangle::Rectangle(Vector2D pos, Vector2D size, Color color, int thickness)
    : Element(pos, color), _size(size) {
        int buf = _size.x;
        if(buf > size.y)
            buf = size.y;
        if(thickness > buf/2)
            _thickness = buf/2;
        else _thickness = thickness;
    }

    Rectangle::Rectangle(Vector2D pos, Vector2D size, Color color)
    : Rectangle(pos, size, color, 1) {}

    void Rectangle::Draw(Vector2D* pos) {
        if(pos == nullptr)
            DrawRectangleLinesEx({_pos.x, _pos.y, _size.x, _size.y}, _thickness, {_color.r, _color.g, _color.b, _color.a});
        else DrawRectangleLinesEx({pos->x, pos->y, _size.x, _size.y}, _thickness, {_color.r, _color.g, _color.b, _color.a});
    }

    bool Rectangle::CheckPosition(Vector2D pos) {
        return pos.x >= _pos.x && pos.x <= _pos.x + _size.x
        && pos.y >= _pos.y && pos.y <= _pos.y + _size.y;
    }

    bool Rectangle::CheckPosition(Vector2D pos1, Vector2D pos2) {
        bool resultX, resultY;
        if(pos1.x <= pos2.x)
            resultX = _pos.x + _size.x >= pos1.x && _pos.x <= pos2.x;
        else resultX = _pos.x + _size.x >= pos2.x && _pos.x <= pos1.x;
        if(pos1.y <= pos2.y)
            resultY = _pos.y + _size.y >= pos1.y && _pos.y <= pos2.y;
        else resultY = _pos.y + _size.y >= pos2.y && _pos.y <= pos1.y;
        return resultX && resultY;
    }
} // l5