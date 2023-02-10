//
// Created by colte on 29.01.2023.
//
#include "imgui_setup.h"

ImGuiRaylibWindow::ImGuiRaylibWindow(const char *title, ImVec2 size, unsigned int flags, Color color)
: _color(color){
    SetConfigFlags(flags);
    InitWindow(size.x, size.y, title);
    SetTargetFPS(144);

    _context = ImGui::CreateContext();
    ImGui::SetCurrentContext(_context);
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    rlImGuiSetup(true);
}

ImGuiRaylibWindow *ImGuiRaylibWindow::CreateWindow(const char *title, ImVec2 size, unsigned int flags, Color color) {
    if(pWindow == nullptr) {
        pWindow = new ImGuiRaylibWindow(title, size, flags, color);
        return pWindow;
    }
    else return nullptr;
}

ImGuiRaylibWindow::~ImGuiRaylibWindow() {
    rlImGuiShutdown();
    CloseWindow();
}

void ImGuiRaylibWindow::Begin() {
    BeginDrawing();
    ClearBackground(_color);
}

void ImGuiRaylibWindow::BeginImGui() {
    rlImGuiBegin();
}

void ImGuiRaylibWindow::EndImGui() {
    rlImGuiEnd();

    if (ImGui::GetIO ().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void ImGuiRaylibWindow::End() {
    EndDrawing();
}

ImGuiRaylibTexture::ImGuiRaylibTexture(ImVec2 size) : _size(size) {
    Image buf = LoadImageFromScreen();
    ImageResize(&buf, _size.x, _size.y);
    _texture = LoadTextureFromImage(buf);
    UnloadImage(buf);
    _pixels = new Color[static_cast<int>(_size.x*_size.y)];
    auto startValues = [](Color** pixels, ImVec2 size) {
        for(int i = 0; i<size.y; i++) {
            for (int j = 0; j < size.x; j++) {
                (*pixels)[static_cast<int>(i*size.x + j)] = BLACK;
            }
        }
    };
    Modify(startValues);
}

ImGuiRaylibTexture::~ImGuiRaylibTexture() {
    UnloadTexture(_texture);
    delete[] _pixels;
}

void ImGuiRaylibTexture::Modify(void (*modifyFunction)(Color **, ImVec2)) {
    modifyFunction(&_pixels, _size);
    UpdateTexture(_texture, _pixels);
}

Texture* ImGuiRaylibTexture::GetTexture() {
    return &_texture;
}

Color **ImGuiRaylibTexture::GetPixels() {
    return &_pixels;
}

ImVec2 ImGuiRaylibTexture::GetSize() {
    return _size;
}
