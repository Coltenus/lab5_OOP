#include <vector>
#include <iostream>
#include <raylib.h>
#include "src/Window.h"
#include "src/Elements/Element.h"
#include "src/common.h"
#include "src/Menu.h"
#include "src/MenuObjects/mobjects.h"
#include "src/Commands/bcommands.h"
#include "src/FigureBuilder.h"

l5::Window* l5::Window::pWindow = nullptr;
bool l5::Element::elementSelected = false;
bool l5::Element::resetSelection = false;
l5::Element* l5::Element::selectedElement = nullptr;
l5::Element* l5::Element::lastElement = nullptr;
bool l5::Group::firstPointSelected = false;

int main(int, char**)
{
    l5::Window* window = l5::Window::CreateWindow("Lab5", {WIDTH, HEIGHT}, FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    while (!WindowShouldClose() && !window->ShouldEnd())
    {
        window->HandleControls();
        window->Update();

        window->Begin();
        window->Draw();
        window->End();

        if(l5::Element::resetSelection) {
            l5::Element::elementSelected = false;
            l5::Element::resetSelection = false;
        }
    }

    delete window;
    window = nullptr;

    return 0;
}

///TODO: Undo/redo ability.
/// Output data into text file.