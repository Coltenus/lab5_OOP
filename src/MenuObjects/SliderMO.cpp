//
// Created by coltenus on 17.02.23.
//
#include "SliderMO.h"

namespace l5{
    template<>
    void SliderMO<float>::Draw(Vector2D pos) {
        DrawText(TextFormat("%4.f", _command->GetMin()), pos.x + GetOffset()[0] + 10, pos.y + GetOffset()[1], _fontH,
                 BLACK);
        DrawText(TextFormat("%4.f", _command->GetMax()), pos.x + GetOffset()[0] + 20 + _width, pos.y + GetOffset()[1],
                 _fontH, BLACK);
        DrawRectangle(pos.x + GetOffset()[0] + 25, pos.y + GetOffset()[1] + _fontH + 5,
                      (float) (_command->GetCurrent() - _command->GetMin()) / (_command->GetMax() - _command->GetMin()) *
                      _width,
                      _fontH, {160, 160, 60, 255});
        DrawRectangle(pos.x + GetOffset()[0] + 25 +
                      (float) (_command->GetCurrent() - _command->GetMin()) / (_command->GetMax() - _command->GetMin()) *
                      _width,
                      pos.y + GetOffset()[1] + _fontH + 5,
                      (float) (_command->GetMax() - _command->GetCurrent()) / (_command->GetMax() - _command->GetMin()) *
                      _width, _fontH, {60, 160, 160, 255});
        DrawText(_text.c_str(), pos.x + GetOffset()[0] + 25, pos.y + GetOffset()[1] + _fontH * 2 + 5, _fontH * 0.8f, BLACK);
    }

}