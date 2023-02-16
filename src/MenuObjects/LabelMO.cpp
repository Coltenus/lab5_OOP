//
// Created by colte on 16.02.2023.
//
#include "LabelMO.h"

namespace l5 {

    template<> void LabelMO<std::string>::Draw(Vector2D pos) {
        if(_value != nullptr && _text.find('%'))
            DrawText(TextFormat(_text.c_str(), _value->c_str()), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
        else DrawText(_text.c_str(), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
    }

    template<> void LabelMO<Vector2>::Draw(Vector2D pos) {
        if(_value != nullptr && _text.find('%'))
            DrawText(TextFormat(_text.c_str(), _value->x, _value->y), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
        else DrawText(_text.c_str(), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
    }
}