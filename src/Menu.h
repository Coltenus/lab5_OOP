//
// Created by colte on 15.02.2023.
//

#ifndef LAB5_MENU_H
#define LAB5_MENU_H

#include "common.h"
#include "MenuObjects/MenuObject.h"
#include <vector>
#include "MenuObjects/mobjects.h"

namespace l5 {

    class Menu {
    private:
        Vector2D _pos, _size;
        ColorSt _color;
        std::vector<MenuObject*> objects;
        bool _isXAxis;
        int _fontH;

    public:
        Menu(Vector2D pos, Vector2D size, ColorSt color, bool isXAxis, int fontH);
        Menu(Vector2D pos, Vector2D size, ColorSt color, bool isXAxis);
        ~Menu();
        void Draw();
        void Update();
        template<typename T = int>
        void Add(MenuObject* object);
    };

    template<typename T>
    void Menu::Add(MenuObject* object) {
        switch (object->GetType()) {
            case 1:
                reinterpret_cast<LabelMO<T>*>(object)->SetFontHeight(_fontH, _isXAxis);
                break;
            case 2:
                reinterpret_cast<ButtonMO*>(object)->SetFontHeight(_fontH, _isXAxis);
                break;
            case 5:
                reinterpret_cast<SliderMO<T>*>(object)->SetFontHeight(_fontH, _isXAxis);
                break;
        }
        objects.push_back(object);
    }

} // l5

#endif //LAB5_MENU_H
