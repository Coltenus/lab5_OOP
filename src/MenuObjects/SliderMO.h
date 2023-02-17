//
// Created by coltenus on 17.02.23.
//

#ifndef LAB5_SLIDERMO_H
#define LAB5_SLIDERMO_H

#include <string>
#include "MenuObject.h"
#include "../Commands/SliderCommand.h"

namespace l5 {

    template <typename T>
    class SliderMO : public MenuObject {
    private:
        int _width, _fontH;
        std::string _text;
        SliderCommand<T>* _command;

    public:
        SliderMO(std::string text, SliderCommand<T>* command, int width = 100);
        ~SliderMO() override;
        void Draw(Vector2D pos) override;
        void Update(Vector2 pos) override;
        void SetFontHeight(int fontH, bool isXAxis);
    };

    template<typename T>
    SliderMO<T>::SliderMO(std::string text, SliderCommand<T>* command, int width)
    : MenuObject(5), _width(width), _fontH(0), _text(text), _command(command) {}

    template<typename T>
    SliderMO<T>::~SliderMO() {
        delete _command;
        _command = nullptr;
    }

    template<typename T>
    void SliderMO<T>::Draw(Vector2D pos) {
        DrawText(TextFormat("%d", _command->GetMin()), pos.x + GetOffset()[0] + 10, pos.y + GetOffset()[1], _fontH, BLACK);
        DrawText(TextFormat("%d", _command->GetMax()), pos.x + GetOffset()[0] + 20 + _width, pos.y + GetOffset()[1], _fontH, BLACK);
        DrawRectangle(pos.x + GetOffset()[0] + 25, pos.y + GetOffset()[1] + _fontH + 5,
                      (float)(_command->GetCurrent() - _command->GetMin())/(_command->GetMax() - _command->GetMin())*_width,
                      _fontH, {160, 160, 60, 255});
        DrawRectangle(pos.x + GetOffset()[0] + 25 + (float)(_command->GetCurrent() - _command->GetMin())/(_command->GetMax() - _command->GetMin())*_width,
                      pos.y + GetOffset()[1] + _fontH + 5,
                      (float)(_command->GetMax() - _command->GetCurrent())/(_command->GetMax() - _command->GetMin())*_width, _fontH, {60, 160, 160, 255});
        DrawText(_text.c_str(), pos.x + GetOffset()[0] + 25, pos.y + GetOffset()[1] + _fontH*2 + 5, _fontH*0.8f, BLACK);
    }

    template<typename T>
    void SliderMO<T>::Update(Vector2 pos) {
        static Vector2 mouse;
        mouse = GetMousePosition();
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)
        && mouse.x >= pos.x + GetOffset()[0] + 25 && mouse.x <= pos.x + GetOffset()[0] + 25 + _width
        && mouse.y >= pos.y + GetOffset()[1] + _fontH + 5 && mouse.y <= pos.y + GetOffset()[1] + _fontH * 2 + 5) {
            _command->MakeAction(mouse.x, pos.x + GetOffset()[0] + 25, pos.x + GetOffset()[0] + 25 + _width);
        }
    }

    template<typename T>
    void SliderMO<T>::SetFontHeight(int fontH, bool isXAxis) {
        _fontH = fontH;
        GetOffset()[0] = _fontH/2;
        GetOffset()[1] = _fontH/2;
        if(isXAxis)
            SetLength(_width + 20);
        else SetLength(_fontH*3);
    }

} // l5

#endif //LAB5_SLIDERMO_H
