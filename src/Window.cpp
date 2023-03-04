//
// Created by colte on 15.02.2023.
//

#include "Window.h"
#include "Commands/ValueSetBC.h"

#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif

l5::OpCode l5::ElementsHistory::opcode = None;
int l5::ElementsHistory::firstPos = -1;
std::vector<int> l5::ElementsHistory::otherPos;

namespace l5 {
    Window::Window(const char *title, Vector2 size, unsigned int flags, Color color)
            : _color(color), _done(false), _clear(true), _saveData(false), _needUndo(false), _needRedo(false),
            _needCopy(false) {
        SetConfigFlags(flags);
        InitWindow(size.x, size.y, title);
        SetTargetFPS(60);

        _menus.push_back(new l5::Menu({0, 0}, {WIDTH, 40}, {50, 220, 30, 255}, true));
        _menus[0]->Add(new l5::LabelMO("Mode: %d", &_builder.mode));
        _menus[0]->Add(new l5::ButtonMO("Undo", new l5::ValueSetBC<bool>(&_needUndo, true)));
        _menus[0]->Add(new l5::ButtonMO("Redo", new l5::ValueSetBC<bool>(&_needRedo, true)));
        _menus[0]->Add(new l5::ButtonMO("Clear", new l5::ValueSetBC<bool>(&_clear, true)));
        _menus[0]->Add(new l5::ButtonMO("Save data", new l5::ValueSetBC<bool>(&_saveData, true)));
        _menus[0]->Add(new l5::ButtonMO("Exit", new l5::ValueSetBC<bool>(&_done, true)));

        _menus.push_back(new l5::Menu({WIDTH - 300, 40}, {400, HEIGHT - 70}, {20, 200, 140, 255}, false, 30));
        _menus[1]->Add(new l5::LabelMO("Select mode"));
        _menus[1]->Add(new l5::ButtonMO("None (0)", new l5::ValueSetBC<int>(&_builder.mode, 0)));
        _menus[1]->Add(new l5::ButtonMO("Circle (1)", new l5::ValueSetBC<int>(&_builder.mode, 1)));
        _menus[1]->Add(new l5::ButtonMO("Rectangle (2)", new l5::ValueSetBC<int>(&_builder.mode, 2)));
        _menus[1]->Add(new l5::ButtonMO("Group (3)", new l5::ValueSetBC<int>(&_builder.mode, 3)));
        _menus[1]->Add(new l5::PreviewMO(&_builder, 220));
        _menus[1]->Add(new l5::EditorMO(&_builder, {200, 350}, false, true));

        _menus.push_back(new l5::Menu({0, HEIGHT - 30}, {WIDTH, 30}, {50, 220, 30, 255}, true));
        _menus[2]->Add(new l5::LabelMO<Vector2>("Mouse position: %4.f, %4.f", &_mousePos));

        _iterator = new ElementIterator(_elements, true);
        _history = new ElementsHistory(_elements);
    }

    Window *Window::CreateWindow(const char *title, Vector2 size, unsigned int flags, Color color) {
        if(pWindow == nullptr) {
            pWindow = new Window(title, size, flags, color);
        }
        return pWindow;
    }

    Window::~Window() {
        delete _history;
        _history = nullptr;

        delete _iterator;
        _iterator = nullptr;

        for(auto el: _elements)
        {
            delete el;
        }

        for(l5::Menu* el: _menus)
            delete el;
        _menus.clear();

        CloseWindow();
    }

    void Window::Begin() {
        BeginDrawing();
        ClearBackground(_color);
    }

    void Window::End() {
        EndDrawing();
    }

    void Window::HandleControls() {
        static Vector2 bufCoord;
        static int bufCh;
        static float wheel;
        _mousePos = GetMousePosition();
        if(_mousePos.x >= WORKSPACE_X_ST && _mousePos.x <= WORKSPACE_X_END
           && _mousePos.y >= WORKSPACE_Y_ST && _mousePos.y <= WORKSPACE_Y_END) {
            _mousePos.x -= WORKSPACE_X_ST;
            _mousePos.y -= WORKSPACE_Y_ST;
        }
        else _mousePos = {0, 0};
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !l5::Element::elementSelected) {
            Vector2 mouse = GetMousePosition();
            if(mouse.x >= WORKSPACE_X_ST && mouse.x <= WORKSPACE_X_END
               && mouse.y >= WORKSPACE_Y_ST && mouse.y <= WORKSPACE_Y_END) {
                l5::Element *buf;
                if(_builder.mode == 3) ElementsHistory::opcode = Assemble;
                else ElementsHistory::opcode = Add;
                ElementsHistory::firstPos = _elements.size();
                switch (_builder.mode) {
                    case 1:
                    case 2:
                        buf = _builder.CreateFigure({mouse.x, mouse.y});
                        if(buf) _elements.push_back(buf);
                        break;
                    case 3:
                        if(l5::Group::firstPointSelected) {
                            l5::Group::firstPointSelected = false;
                            auto bufElements = l5::Group::FindElements({bufCoord.x, bufCoord.y}, {mouse.x, mouse.y}, _elements);
                            l5::Vector2D pos = l5::Group::FindCorrectPos({bufCoord.x, bufCoord.y}, {mouse.x, mouse.y});
                            l5::Vector2D size = l5::Group::FindSize({bufCoord.x, bufCoord.y}, {mouse.x, mouse.y});
                            buf = _builder.CreateFigure(pos, &bufElements, size);
                            if(buf) _elements.push_back(buf);
                        } else {
                            bufCoord = mouse;
                            l5::Group::firstPointSelected = true;
                        }
                        break;
                }
                if(ElementsHistory::opcode == Assemble)
                    ElementsHistory::firstPos -= ElementsHistory::otherPos.size();
                if(l5::Group::firstPointSelected)
                    ElementsHistory::opcode = None;
            }
            else {
                l5::Group::firstPointSelected = false;
            }
        }
        else if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_DELETE)) {
            _clear = true;
        }
        else if((bufCh = GetCharPressed()) >= 48 && bufCh <= 51)
            _builder.mode = bufCh - 48;
        else if(IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            l5::Group* bufElement = dynamic_cast<l5::Group *>(l5::Group::FindElement({_mousePos.x, _mousePos.y},
                                                                                     _elements));
            if(l5::Element::selectedElement) {
                if(bufElement) {
                    auto el = _elements.begin();
                    while(*el != Element::selectedElement) {
                        el++;
                    }
                    if(el != _elements.end()) {
                        ElementsHistory::opcode = AddToGroup;
                        ElementsHistory::otherPos.push_back(el - _elements.begin());
                        _elements.erase(el);
                        el = _elements.begin();
                        while(*el != bufElement) {
                            el++;
                        }
                        ElementsHistory::firstPos = (int)(_elements.begin() - el);
                        bufElement->AddElement(l5::Element::selectedElement);
                        Element::ReplacePointer(l5::Element::selectedElement, _elements);
                    }
                }
                l5::Element::selectedElement->HandleElementSelection();
            }
        }
        else if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D)) {
            _needCopy = true;
        }
        else if((wheel = GetMouseWheelMove()) != 0) {
            _builder.mode -= wheel;
            if(_builder.mode < 0) _builder.mode = 3;
            if(_builder.mode > 3) _builder.mode = 0;
        }
        else if(IsKeyPressed(KEY_TAB)) {
            Element::selectedElement = _iterator->NextElement();
        }
        else if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_Z)) {
            _needRedo = true;
        }
        else if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
            _needUndo = true;
        }
    }

    void Window::Update() {
        if(_history->Check()) {
            _history->AddUndo();
        }

        for(auto& el: _elements)
            el->Update();

        for(auto el = _elements.begin(); el != _elements.end() && _elements.size(); el++) {
            if((*el)->NeedRemoval()) {
                ElementsHistory::opcode = Remove;
                ElementsHistory::firstPos = el - _elements.begin();
                Element::ReplacePointer(*el, _elements);
                delete *el;
                _elements.erase(el);
                el = _elements.begin();
            }
        }

        if(_clear) {
            for(auto el: _elements)
                delete el;
            _elements.clear();
            _clear = false;
            Element::HandleSelection();
            Element::selectedElement = nullptr;
            _history->Clear();
        }

        if(_saveData) {
            FILE* file;
            if(!fopen_s(&file, "figures_data.txt", "wt")) {
                std::string buffer;
                for(auto& el: _elements) {
                    if(el->GetType() != 3) buffer = el->GetTextData();
                    else buffer = el->GetTextData(nullptr, false, false);
                    fprintf(file, "%s\n", buffer.c_str());
                }
                fclose(file);
            }
            _saveData = false;
        }

        if(_needUndo) {
            if(Element::selectedElement)
                Element::selectedElement->HandleElementSelection();
            _history->Undo();
            _needUndo = false;
        }

        if(_needRedo) {
            if(Element::selectedElement)
                Element::selectedElement->HandleElementSelection();
            _history->Redo();
            _needRedo = false;
        }

        if(_needCopy) {
            if(l5::Element::selectedElement) {
                Element* buf = FigureBuilder::ConvertChildClass(l5::Element::selectedElement);
                buf->SetPointer();
                _elements.push_back(buf);
                l5::Element::selectedElement->HandleElementSelection();
            }
            _needCopy = false;
        }

        for(auto& el: _menus)
            el->Update();
    }

    void Window::Draw() {
        for(auto& el: _elements)
            el->Draw();

        for(auto& el: _menus)
            el->Draw();
    }

    bool Window::ShouldEnd() {
        return _done;
    }
} // l5