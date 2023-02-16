#include <vector>
#include <iostream>
#include <raylib.h>
#include "src/Window.h"
#include "src/Elements/elements.h"
#include "src/common.h"
#include "src/Menu.h"
#include "src/MenuObjects/mobjects.h"

l5::Window* l5::Window::pWindow = nullptr;
bool l5::Element::elementSelected = false;
bool l5::Element::resetSelection = false;

int main(int, char**)
{
    l5::Window* window = l5::Window::CreateWindow("Lab5", {WIDTH, HEIGHT}, FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    std::vector<l5::Element*> elements = {
            new l5::Circle({600, 400}, 30, {0, 0, 0, 255}, 10),
            new l5::Rectangle({200, 600}, {100, 50}, {0, 0, 0, 255}, 15)
    };

    int mode = 1;
    bool done = false;

    l5::Menu* titleMenu = new l5::Menu({0, 0}, {WIDTH, 40}, {50, 220, 30, 255}, true);
    titleMenu->Add(new l5::LabelMO<int>("Mode: %d", &mode));
    titleMenu->Add<bool>(new l5::ButtonMO<bool>("Exit", &done, true));

    l5::Menu* selectionMenu = new l5::Menu({WIDTH - 300, 40}, {400, HEIGHT - 40}, {20, 200, 140, 255}, false, 30);
    selectionMenu->Add(new l5::LabelMO<int>("Select mode"));
    selectionMenu->Add(new l5::ButtonMO<int>("Circle", &mode, 1));
    selectionMenu->Add(new l5::ButtonMO<int>("Rectangle", &mode, 2));
    selectionMenu->Add(new l5::ButtonMO<int>("Group", &mode, 3));

    while (!WindowShouldClose() && !done)
    {
        for(auto& el: elements)
            el->Update();

        titleMenu->Update();
        selectionMenu->Update();

        window->Begin();

        for(auto& el: elements)
            el->Draw();

        titleMenu->Draw();
        selectionMenu->Draw();

        window->End();
        if(l5::Element::resetSelection) {
            l5::Element::elementSelected = false;
            l5::Element::resetSelection = false;
        }
    }

    for(auto el: elements)
        delete el;

    delete titleMenu;
    titleMenu = nullptr;
    delete selectionMenu;
    selectionMenu = nullptr;

    delete window;
    window = nullptr;

    return 0;
}

///TODO: Make Builder class with prototypes and it can draw prototype in given position.
/// Need to connect it with preview class.
/// Make possible create and delete figures.