//
// Created by colte on 15.02.2023.
//

#include "Window.h"

namespace l5 {
    Window::Window(const char *title, Vector2 size, unsigned int flags, Color color)
            : _color(color){
        SetConfigFlags(flags);
        InitWindow(size.x, size.y, title);
        SetTargetFPS(60);
    }

    Window *Window::CreateWindow(const char *title, Vector2 size, unsigned int flags, Color color) {
        if(pWindow == nullptr) {
            pWindow = new Window(title, size, flags, color);
        }
        return pWindow;
    }

    Window::~Window() {
        CloseWindow();
    }

    void Window::Begin() {
        BeginDrawing();
        ClearBackground(_color);
    }

    void Window::End() {
        EndDrawing();
    }
} // l5