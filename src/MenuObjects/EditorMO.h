//
// Created by coltenus on 17.02.23.
//

#ifndef LAB5_EDITORMO_H
#define LAB5_EDITORMO_H

#include <string>
#include "MenuObject.h"
#include "../FigureBuilder.h"
#include "../Commands/SliderCommand.h"

namespace l5 {

    class EditorMO : public MenuObject {
    private:
        FigureBuilder* _builder;
        Vector2D _size;
        bool _needFrame;
        std::vector<MenuObject*> *_visible, _circle, _rectangle, _group;
        int _mode, _fontH;
        bool _isXAxis;
        void changeState();
        template<typename T>
        void ConvertSlider(std::string text, SliderCommand<T>* command,
                           std::vector<MenuObject*> *objects, float fontK = 1, int width = 100);

    public:
        EditorMO(FigureBuilder* builder, Vector2D size, bool isXAxis, bool needFrame = false);
        ~EditorMO() override;
        void Draw(Vector2D pos) override;
        void Update(Vector2 pos) override;
    };

} // l5

#endif //LAB5_EDITORMO_H
