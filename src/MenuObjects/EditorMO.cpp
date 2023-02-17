//
// Created by coltenus on 17.02.23.
//

#include "EditorMO.h"
#include "mobjects.h"

namespace l5 {
    EditorMO::EditorMO(FigureBuilder *builder, Vector2D size, bool isXAxis, bool needFrame)
    : MenuObject(4), _builder(builder), _size(size), _needFrame(needFrame), _visible(nullptr),
    _mode(0), _fontH(20), _isXAxis(isXAxis) {
        if(_isXAxis) SetLength(_size.x);
        else SetLength(_size.y);
        GetOffset()[0] = 25;
        GetOffset()[1] = 15;
        {
            MenuObject* object;
            object = new LabelMO("Circle");
            reinterpret_cast<LabelMO<int>*>(object)->SetFontHeight(_fontH, false);
            _circle.push_back(object);
            ConvertSlider("Radius", new SliderCommand<int>(_builder->GetCircle()->GetRadiusP(), 10, 100), &_circle, 3.f/4);
            ConvertSlider("Thickness", new SliderCommand<int>(_builder->GetCircle()->GetThicknessP(), 1, 100), &_circle, 3.f/4);
            ConvertSlider("Red", new SliderCommand<unsigned char>(_builder->GetCircle()->GetRedP(), 0, 255), &_circle, 1.f/2);
            ConvertSlider("Green", new SliderCommand<unsigned char >(_builder->GetCircle()->GetGreenP(), 0, 255), &_circle, 1.f/2);
            ConvertSlider("Blue", new SliderCommand<unsigned char>(_builder->GetCircle()->GetBlueP(), 0, 255), &_circle, 1.f/2);
            object = new LabelMO("Rectangle");
            reinterpret_cast<LabelMO<int>*>(object)->SetFontHeight(_fontH, false);
            _rectangle.push_back(object);
            ConvertSlider("Width", new SliderCommand<float>(_builder->GetRectangle()->GetSizeXP(), 10, 100), &_rectangle, 3.f/4);
            ConvertSlider("Height", new SliderCommand<float>(_builder->GetRectangle()->GetSizeYP(), 10, 100), &_rectangle, 3.f/4);
            ConvertSlider("Thickness", new SliderCommand<int>(_builder->GetRectangle()->GetThickness(), 1, 100), &_rectangle, 3.f/4);
            ConvertSlider("Red", new SliderCommand<unsigned char>(_builder->GetRectangle()->GetRedP(), 0, 255), &_rectangle, 1.f/2);
            ConvertSlider("Green", new SliderCommand<unsigned char >(_builder->GetRectangle()->GetGreenP(), 0, 255), &_rectangle, 1.f/2);
            ConvertSlider("Blue", new SliderCommand<unsigned char>(_builder->GetRectangle()->GetBlueP(), 0, 255), &_rectangle, 1.f/2);
            object = new LabelMO("Group");
            reinterpret_cast<LabelMO<int>*>(object)->SetFontHeight(_fontH, false);
            _group.push_back(object);
        }
    }

    void EditorMO::Draw(Vector2D pos) {
        static int length;
        if(_needFrame)
            DrawRectangleLinesEx({pos.x + GetOffset()[0], pos.y + GetOffset()[1], _size.x, _size.y}, 2, BLACK);
        if(_visible) {
            length = 0;
            for(auto& el: *_visible) {
                if(_isXAxis)
                    el->Draw({pos.x + GetOffset()[0] + length, pos.y + GetOffset()[1]});
                else el->Draw({pos.x + GetOffset()[0], pos.y + GetOffset()[1] + length});
                length += el->GetLength() + OBJECTS_DIST;
            }
        }
    }

    void EditorMO::Update(Vector2 pos) {
        static int length;
        changeState();
        if(_visible) {
            length = 0;
            for(auto& el: *_visible) {
                if(_isXAxis)
                    el->Update({pos.x + GetOffset()[0] + length, pos.y + GetOffset()[1]});
                else el->Update({pos.x + GetOffset()[0], pos.y + GetOffset()[1] + length});
                length += el->GetLength() + OBJECTS_DIST;
            }
        }
    }

    void EditorMO::changeState() {
        if(_mode != _builder->mode) {
            _mode = _builder->mode;
            switch (_mode) {
                case 1:
                    _visible = &_circle;
                    break;
                case 2:
                    _visible = &_rectangle;
                    break;
                case 3:
                    _visible = &_group;
                    break;
                default:
                    _visible = nullptr;
                    break;
            }
        }
    }

    EditorMO::~EditorMO() {
        for(MenuObject* el: _circle)
            delete el;
        _circle.clear();
        for(MenuObject* el: _rectangle)
            delete el;
        _rectangle.clear();
        for(MenuObject* el: _group)
            delete el;
        _group.clear();
    }

    template<typename T>
    void
    EditorMO::ConvertSlider(std::string text, SliderCommand<T> *command, std::vector<MenuObject *> *objects,
                            float fontK, int width) {
        auto object = new SliderMO<T>(text, command, width);
        reinterpret_cast<SliderMO<T>*>(object)->SetFontHeight((float)_fontH*fontK, _isXAxis);
        objects->push_back(object);
    }
} // l5