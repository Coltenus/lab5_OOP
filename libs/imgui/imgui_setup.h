//
// Created by colte on 29.01.2023.
//

#ifndef IMGUITESTS_IMGUI_SETUP_H
#define IMGUITESTS_IMGUI_SETUP_H

#include "src/imgui.h"
#include "src/rlImGui.h"
#include "src/rlImGuiColors.h"
#include <raylib.h>

class ImGuiRaylibWindow {
private:
    ImGuiContext* _context;
    Color _color;
    ImGuiRaylibWindow(const char* title, ImVec2 size, unsigned int flags, Color color);

public:
    static ImGuiRaylibWindow* pWindow;
    static ImGuiRaylibWindow* CreateWindow(const char* title, ImVec2 size,
    unsigned int flags = FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE,
    Color color = (Color){140, 140, 140, 255});
    ~ImGuiRaylibWindow();
    void Begin();
    void BeginImGui();
    void EndImGui();
    void End();
};

class ImGuiRaylibTexture {
private:
    Texture _texture;
    Color* _pixels;
    ImVec2 _size;

public:
    ImGuiRaylibTexture(ImVec2 size);
    ~ImGuiRaylibTexture();
    void Modify(void (*modifyFunction)(Color**, ImVec2));
    Texture* GetTexture();
    Color** GetPixels();
    ImVec2 GetSize();
};

#endif //IMGUITESTS_IMGUI_SETUP_H
