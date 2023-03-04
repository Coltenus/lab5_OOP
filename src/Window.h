//
// Created by colte on 15.02.2023.
//

#ifndef LAB5_WINDOW_H
#define LAB5_WINDOW_H

#include <raylib.h>
#include "FigureBuilder.h"
#include "Menu.h"
#include "ElementIterator.h"
#include "ElementsHistory.h"

namespace l5 {

    class Window {
    private:
        Color _color;
        Window(const char* title, Vector2 size, unsigned int flags, Color color);
        FigureBuilder _builder;
        std::vector<Element*> _elements;
        bool _done, _clear, _saveData, _needUndo, _needRedo, _needCopy;
        Vector2 _mousePos;
        std::vector<l5::Menu*> _menus;
        ElementIterator* _iterator;
        ElementsHistory* _history;

    public:
        static Window* pWindow;
        static Window* CreateWindow(const char* title, Vector2 size,
        unsigned int flags = FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE,
        Color color = (Color){200, 200, 200, 255});
        ~Window();
        void Begin();
        void End();
        void HandleControls();
        void Update();
        void Draw();
        bool ShouldEnd();
    };

} // l5

#endif //LAB5_WINDOW_H
