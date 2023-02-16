//
// Created by colte on 15.02.2023.
//

#include "Menu.h"
#include <raylib.h>

namespace l5 {
    Menu::Menu(Vector2D pos, Vector2D size, ColorSt color, bool isXAxis, int fontH)
    : _pos(pos), _size(size), _color(color), _isXAxis(isXAxis), _fontH(fontH) {}

    Menu::Menu(Vector2D pos, Vector2D size, ColorSt color, bool isXAxis)
    : Menu(pos, size, color, isXAxis, 20) {}

    Menu::~Menu() {
        for(auto el: objects)
            delete el;
    }

    void Menu::Draw() {
        static int length;
        DrawRectangleRec({_pos.x, _pos.y, _size.x, _size.y}, (Color){_color.r, _color.g, _color.b, _color.a});
        length = 0;
        if(_isXAxis) {
            for (auto &el: objects) {
                el->Draw({_pos.x + length, _pos.y});
                length += el->GetLength() + OBJECTS_DIST;
            }
        }
        else {
            for (auto &el: objects) {
                el->Draw({_pos.x, _pos.y + length});
                length += el->GetLength() + OBJECTS_DIST;
            }
        }
    }

    void Menu::Update() {
        static int length;
        length = 0;
        if(_isXAxis) {
            for (auto &el: objects) {
                el->Update({_pos.x + length, _pos.y});
                length += el->GetLength() + OBJECTS_DIST;
            }
        }
        else {
            for (auto &el: objects) {
                el->Update({_pos.x, _pos.y + length});
                length += el->GetLength() + OBJECTS_DIST;
            }
        }

    }
} // l5