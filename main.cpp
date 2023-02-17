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
bool l5::Group::firstPointSelected = false;

int main(int, char**)
{
    l5::Window* window = l5::Window::CreateWindow("Lab5", {WIDTH, HEIGHT}, FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);

    l5::FigureBuilder builder;

    std::vector<l5::Element*> elements;

    bool done = false;
    Vector2 bufCoord, mousePos;
    int bufCh;

    std::vector<l5::Menu*> menus;
    menus.push_back(new l5::Menu({0, 0}, {WIDTH, 40}, {50, 220, 30, 255}, true));
    menus[0]->Add(new l5::LabelMO("Mode: %d", &builder.mode));
    menus[0]->Add(new l5::ButtonMO("Exit", new l5::ValueSetBC<bool>(&done, true)));

    menus.push_back(new l5::Menu({WIDTH - 300, 40}, {400, HEIGHT - 70}, {20, 200, 140, 255}, false, 30));
    menus[1]->Add(new l5::LabelMO("Select mode"));
    menus[1]->Add(new l5::ButtonMO("None (0)", new l5::ValueSetBC<int>(&builder.mode, 0)));
    menus[1]->Add(new l5::ButtonMO("Circle (1)", new l5::ValueSetBC<int>(&builder.mode, 1)));
    menus[1]->Add(new l5::ButtonMO("Rectangle (2)", new l5::ValueSetBC<int>(&builder.mode, 2)));
    menus[1]->Add(new l5::ButtonMO("Group (3)", new l5::ValueSetBC<int>(&builder.mode, 3)));
    menus[1]->Add(new l5::PreviewMO(&builder, 220));
    menus[1]->Add(new l5::EditorMO(&builder, {200, 350}, false, true));

    menus.push_back(new l5::Menu({0, HEIGHT - 30}, {WIDTH, 30}, {50, 220, 30, 255}, true));
    menus[2]->Add(new l5::LabelMO<Vector2>("Mouse position: %4.f, %4.f", &mousePos));

    while (!WindowShouldClose() && !done)
    {
        mousePos = GetMousePosition();
        if(mousePos.x >= WORKSPACE_X_ST && mousePos.x <= WORKSPACE_X_END
           && mousePos.y >= WORKSPACE_Y_ST && mousePos.y <= WORKSPACE_Y_END) {
            mousePos.x -= WORKSPACE_X_ST;
            mousePos.y -= WORKSPACE_Y_ST;
        }
        else mousePos = {0, 0};
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !l5::Element::elementSelected) {
            Vector2 mouse = GetMousePosition();
            if(mouse.x >= WORKSPACE_X_ST && mouse.x <= WORKSPACE_X_END
               && mouse.y >= WORKSPACE_Y_ST && mouse.y <= WORKSPACE_Y_END) {
                l5::Element *buf;
                switch (builder.mode) {
                    case 1:
                    case 2:
                        buf = builder.CreateFigure({mouse.x, mouse.y});
                        if(buf) elements.push_back(buf);
                        break;
                    case 3:
                        if(l5::Group::firstPointSelected) {
                            l5::Group::firstPointSelected = false;
                            auto bufElements = l5::Group::FindElements({bufCoord.x, bufCoord.y}, {mouse.x, mouse.y}, elements);
                            l5::Vector2D pos = l5::Group::FindCorrectPos({bufCoord.x, bufCoord.y}, {mouse.x, mouse.y});
                            l5::Vector2D size = l5::Group::FindSize({bufCoord.x, bufCoord.y}, {mouse.x, mouse.y});
                            buf = builder.CreateFigure(pos, &bufElements, size);
                            if(buf) elements.push_back(buf);
                        } else {
                            bufCoord = mouse;
                            l5::Group::firstPointSelected = true;
                        }
                        break;
                }
            }
            else {
                l5::Group::firstPointSelected = false;
            }
        }
        else if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_DELETE)) {
            for(auto el: elements)
                delete el;
            elements.clear();
        }
        else if((bufCh = GetCharPressed()) >= 48 && bufCh <= 57)
            builder.mode = bufCh - 48;

        for(auto& el: elements)
            el->Update();

        for(auto el = elements.begin(); el != elements.end() && elements.size(); el++) {
            if((*el)->NeedRemoval()) {
                delete *el;
                elements.erase(el);
                el = elements.begin();
            }
        }

        for(auto& el: menus)
            el->Update();

        window->Begin();

        for(auto& el: elements)
            el->Draw();

        for(auto& el: menus)
            el->Draw();

        window->End();
        if(l5::Element::resetSelection) {
            l5::Element::elementSelected = false;
            l5::Element::resetSelection = false;
        }
    }

    for(auto el: elements)
        delete el;

    for(l5::Menu* el: menus)
        delete el;
    menus.clear();

    delete window;
    window = nullptr;

    return 0;
}

///TODO: Add element to group.
/// Copy element.
/// Undo/redo ability.
/// Ability to pass all elements(maybe select every elemnt)(pattern iterator)
/// Output data into text file.