//
// Created by colte on 15.02.2023.
//

#ifndef LAB5_WINDOW_H
#define LAB5_WINDOW_H

#include <raylib.h>

namespace l5 {

    class Window {
    private:
        Color _color;
        Window(const char* title, Vector2 size, unsigned int flags, Color color);

    public:
        static Window* pWindow;
        static Window* CreateWindow(const char* title, Vector2 size,
        unsigned int flags = FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE,
        Color color = (Color){140, 140, 140, 255});
        ~Window();
        void Begin();
        void End();
    };

} // l5

#endif //LAB5_WINDOW_H
