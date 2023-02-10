#include <vector>
#include <iostream>
#include "libs/imgui/imgui_setup.h"
#include "src/Circle.h"
#include "src/Rectangle.h"

ImGuiRaylibWindow* ImGuiRaylibWindow::pWindow = nullptr;
bool l5::Element::elementSelected = false;
bool l5::Element::resetSelection = false;

int main(int, char**)
{
    ImGuiRaylibWindow* window = ImGuiRaylibWindow::CreateWindow("Lab5", {1600, 900}, FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    std::vector<l5::Element*> elements = {
            new l5::Circle({600, 400}, 30, {0, 0, 0, 255}, 10),
            new l5::Rectangle({200, 600}, {100, 50}, {0, 0, 0, 255}, 15)
    };

    int mode = 1;

    bool done = false;
    bool demoShow = false;
    bool selection = true;
    while (!WindowShouldClose() && !done)
    {
        for(auto& el: elements)
            el->Update();

        window->Begin();

        DrawText(TextFormat("Mode: %d", mode), 20, 20, 30, BLACK);

        for(auto& el: elements)
            el->Draw();

        window->BeginImGui();

        if(ImGui::BeginMainMenuBar()) {
            if(ImGui::BeginMenu("File")) {
                ImGui::MenuItem("Demo show", nullptr, &demoShow);
                ImGui::MenuItem("Figure selection", nullptr, &selection);
                ImGui::Separator();
                ImGui::MenuItem("Exit", nullptr, &done);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        if(demoShow)
            ImGui::ShowDemoWindow(&demoShow);

        if(selection) {
            ImGui::SetNextWindowSize((ImVec2) {300, 200}, ImGuiCond_Once);
            ImGui::SetNextWindowPos((ImVec2) {1300, 20}, ImGuiCond_Once);
            ImGui::Begin("Figure selection", &selection, ImGuiWindowFlags_NoResize);

            ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);
            if(ImGui::TreeNode("Mode")) {
                ImGui::RadioButton("Circle", &mode, 1);
                ImGui::RadioButton("Rectangle", &mode, 2);
                ImGui::RadioButton("Group", &mode, 3);
                ImGui::TreePop();
            }

            ImGui::End();
        }

        window->EndImGui();

        window->End();
        if(l5::Element::resetSelection) {
            l5::Element::elementSelected = false;
            l5::Element::resetSelection = false;
        }
    }

    for(auto el: elements)
        delete el;

    delete window;
    window = nullptr;

    return 0;
}