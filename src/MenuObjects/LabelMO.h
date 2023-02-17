//
// Created by colte on 15.02.2023.
//

#ifndef LAB5_LABELMO_H
#define LAB5_LABELMO_H

#include <string>
#include <vector>
#include "MenuObject.h"
#include <raylib.h>

namespace l5 {

    template<typename T = int>
    class LabelMO : public MenuObject {
    private:
        std::string _text;
        T* _value;
        int _fontH;

    public:
        LabelMO(std::string text, T* value);
        LabelMO(std::string text);
        ~LabelMO() override = default;
        void Draw(Vector2D pos) override;
        void Update(Vector2 pos) override;
        void SetFontHeight(int fontH, bool isXAxis);
    };

    template<typename T>
    LabelMO<T>::LabelMO(std::string text, T* value)
    : MenuObject(1), _text(text), _value(value), _fontH(0) {}

    template<typename T>
    LabelMO<T>::LabelMO(std::string text)
    : LabelMO(text, nullptr) {}

    template<typename T>
    void LabelMO<T>::Draw(Vector2D pos) {
        if(_value != nullptr && _text.find('%'))
            DrawText(TextFormat(_text.c_str(), *_value), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
        else DrawText(_text.c_str(), pos.x + GetOffset()[0], pos.y + GetOffset()[1], _fontH, BLACK);
    }

    template<typename T>
    void LabelMO<T>::Update(Vector2 pos) {}

    template<typename T>
    void LabelMO<T>::SetFontHeight(int fontH, bool isXAxis) {
        _fontH = fontH;
        GetOffset()[0] = _fontH/2;
        GetOffset()[1] = _fontH/2;
        if(isXAxis)
            SetLength(_text.length()*_fontH*0.6);
        else SetLength(_fontH);
    }

    template<> void LabelMO<Vector2>::Draw(Vector2D pos);
    template<> void LabelMO<std::string>::Draw(Vector2D pos);
} // l5

#endif //LAB5_LABELMO_H
