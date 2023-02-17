//
// Created by colte on 16.02.2023.
//

#include "FigureBuilder.h"
#include <raylib.h>

namespace l5 {
    FigureBuilder::FigureBuilder() : mode(0) {
        std::vector<Element*> buf;
        _circle = new l5::Circle({0, 0}, 30, {0, 0, 0, 255}, 10);
        _rectangle = new l5::Rectangle({0, 0}, {50, 50}, {0, 0, 0, 255}, 15);
        _group = new l5::Group({0, 0}, {0, 0}, buf);
    }

    FigureBuilder::~FigureBuilder() {
        delete _circle;
        _circle = nullptr;
        delete _rectangle;
        _rectangle = nullptr;
        delete _group;
        _group = nullptr;
    }

    Element *FigureBuilder::CreateFigure(Vector2D pos, std::vector<Element *> *elements, Vector2D size) {
        Element* result = nullptr;
        switch (mode) {
            case 1:
                result = new Circle(_circle);
                break;
            case 2:
                result = new Rectangle(_rectangle);
                break;
            case 3:
                result = new Group(_group);
                reinterpret_cast<Group*>(result)->SetSize(size);
        }
        if(result) {
            result->SetPos(pos);
            if (mode == 3 && elements)
                reinterpret_cast<Group *>(result)->SetElements(*elements);
        }
        return result;
    }

    void FigureBuilder::Draw(Vector2D* pos) const {
        switch (mode) {
            case 1:
                if(pos)
                    _circle->Draw(pos);
                break;
            case 2:
                if(pos)
                    _rectangle->Draw(pos);
                break;
            case 3:
                if(pos)
                    DrawRectangleLinesEx({pos->x - 50, pos->y - 50, 100, 100}, 2, {0, 0, 0, 150});
                break;
        }
    }

    Circle *FigureBuilder::GetCircle() {
        return _circle;
    }

    Rectangle *FigureBuilder::GetRectangle() {
        return _rectangle;
    }

    Group *FigureBuilder::GetGroup() {
        return _group;
    }
} // l5