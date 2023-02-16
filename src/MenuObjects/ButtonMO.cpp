//
// Created by colte on 16.02.2023.
//
#include "ButtonMO.h"
#include <utility>

namespace l5 {

    ButtonMO::ButtonMO(std::string text, ButtonCommand* command)
            : MenuObject(2), _text(std::move(text)), _command(command), _fontH(0), _size({0, 0}) {}

    void ButtonMO::Draw(Vector2D pos) {
        DrawText(_text.c_str(), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
        DrawRectangleLinesEx({pos.x + GetOffset()[0] - BTN_SIZE_OFFSET,
                              pos.y + GetOffset()[1] - BTN_SIZE_OFFSET, _size.x, _size.y}, 2, BLACK);
    }

    void ButtonMO::Update(Vector2 pos) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
           && mouse.x >= pos.x + GetOffset()[0] - BTN_SIZE_OFFSET
           && mouse.x <= pos.x + GetOffset()[0] - BTN_SIZE_OFFSET + _size.x
           && mouse.y >= pos.y + GetOffset()[1] - BTN_SIZE_OFFSET
           && mouse.y <= pos.y + GetOffset()[1] - BTN_SIZE_OFFSET + _size.y)
            _command->MakeAction();
    }

    void ButtonMO::SetFontHeight(int fontH, bool isXAxis) {
        _fontH = fontH;
        GetOffset()[0] = _fontH/2;
        GetOffset()[1] = _fontH/2;
        _size = {_text.length()*fontH*0.6f, (float)_fontH};
        if(isXAxis) {
            SetLength(_size.x);
        }
        else {
            SetLength(_size.y);
        }
        _size.x += BTN_SIZE_OFFSET * 2;
        _size.y += BTN_SIZE_OFFSET * 2;
    }

}