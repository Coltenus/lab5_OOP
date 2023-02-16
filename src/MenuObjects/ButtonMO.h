//
// Created by colte on 15.02.2023.
//

#ifndef LAB5_BUTTONMO_H
#define LAB5_BUTTONMO_H

#include "MenuObject.h"
#include <string>
#include <raylib.h>
#include "../ButtonCommands/ButtonCommand.h"

namespace l5 {
#define BTN_SIZE_OFFSET 3
    
    class ButtonMO : public MenuObject {
    private:
        std::string _text;
        ButtonCommand* _command;
        int _fontH;
        Vector2 _size;

    public:
        ButtonMO(std::string text, ButtonCommand* command);
        ~ButtonMO() override = default;
        void Draw(Vector2D pos) override;
        void Update(Vector2 pos) override;
        void SetFontHeight(int fontH, bool isXAxis);
    };

} // l5

#endif //LAB5_BUTTONMO_H
