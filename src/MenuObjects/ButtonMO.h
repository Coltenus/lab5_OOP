//
// Created by colte on 15.02.2023.
//

#ifndef LAB5_BUTTONMO_H
#define LAB5_BUTTONMO_H

#include "MenuObject.h"
#include <string>
#include <raylib.h>

#define BTN_SIZE_OFFSET 3
namespace l5 {
    
    template<typename T>
    class ButtonMO : public MenuObject {
    private:
        std::string _text;
        T* _dest;
        T _value;
        int _fontH;
        Vector2 _size;

    public:
        ButtonMO(std::string text, T* dest, T value);
        ~ButtonMO() override = default;
        void Draw(Vector2D pos) override;
        void Update(Vector2 pos) override;
        void SetFontHeight(int fontH, bool isXAxis);
    };

    template<typename T>
    ButtonMO<T>::ButtonMO(std::string text, T *dest, T value)
    : MenuObject(2), _text(text), _dest(dest), _value(value), _fontH(0), _size({0, 0}) {}

    template<typename T>
    void ButtonMO<T>::Draw(Vector2D pos) {
        DrawText(_text.c_str(), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
        DrawRectangleLinesEx({pos.x + GetOffset()[0] - BTN_SIZE_OFFSET,
        pos.y + GetOffset()[1] - BTN_SIZE_OFFSET, _size.x, _size.y}, 2, BLACK);
    }

    template<typename T>
    void ButtonMO<T>::Update(Vector2 pos) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        && mouse.x >= pos.x + GetOffset()[0] - BTN_SIZE_OFFSET
        && mouse.x <= pos.x + GetOffset()[0] - BTN_SIZE_OFFSET + _size.x
        && mouse.y >= pos.y + GetOffset()[1] - BTN_SIZE_OFFSET
        && mouse.y <= pos.y + GetOffset()[1] - BTN_SIZE_OFFSET + _size.y)
            *_dest = _value;
    }

    template<typename T>
    void ButtonMO<T>::SetFontHeight(int fontH, bool isXAxis) {
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

} // l5

#endif //LAB5_BUTTONMO_H
