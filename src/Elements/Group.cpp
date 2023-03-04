//
// Created by colte on 10.02.2023.
//

#include "Group.h"
#include "elements.h"
#include <raylib.h>
#include "../FigureBuilder.h"
#include "../ElementsHistory.h"

namespace l5 {
    Group::Group(Vector2D pos, Vector2D size, std::vector<Element *>& elements)
    : Element(3, pos, {0, 0, 0, 0}), _size(size), _elements(elements) {
        Vector2D buf;
        for(auto& el: _elements) {
            buf = el->GetPos();
            _elementsPos.push_back({buf.x - _pos.x, buf.y - _pos.y});
        }
    }

    Group::Group(Group &group)
    : Element(group), _size(group._size), _elementsPos(group._elementsPos) {
        for(Element* el: group._elements) {
            Element* buf = FigureBuilder::ConvertChildClass(el);
            if(buf) {
                _elements.push_back(buf);
            }
        }
    }

    Group::Group(Group *group)
    : Element(group), _size(group->_size), _elementsPos(group->_elementsPos) {
        for(Element* el: group->_elements) {
            Element* buf = FigureBuilder::ConvertChildClass(el);
            if(buf) {
                _elements.push_back(buf);
            }
        }
    }

    void Group::Draw(Vector2D *pos) {
        unsigned char a;
        Vector2D vec;
        if(_isSelected) a = 80;
        else a = 150;
        if(pos) DrawRectangleLinesEx({pos->x, pos->y, _size.x, _size.y}, 2, {0, 0, 0, a});
        else DrawRectangleLinesEx({_pos.x, _pos.y, _size.x, _size.y}, 2, {0, 0, 0, a});
        for(int i = 0; i < _elements.size(); i++) {
            vec = _elementsPos[i];
            if(pos) vec = {pos->x + vec.x, pos->y + vec.y};
            else vec = {_pos.x + vec.x, _pos.y + vec.y};
            _elements[i]->Draw(&vec);
        }
    }

    bool Group::CheckPosition(Vector2D mouse, Vector2D* pos) {
        Vector2D vec;
        bool result = false;
        if(!_elements.empty()) {
            for (int i = 0; i < _elements.size(); i++) {
                vec = _elementsPos[i];
                if(pos) vec = {pos->x + vec.x, pos->y + vec.y};
                else vec = {_pos.x + vec.x, _pos.y + vec.y};
                if (_elements[i]->CheckPosition(mouse, &vec))
                    result = true;
                if (result)
                    break;
            }
        }
        else {
            result = mouse.x >= _pos.x && mouse.x <= _pos.x + _size.x
                    && mouse.y >= _pos.y && mouse.y <= _pos.y + _size.y;
        }
        return result;
    }

    bool Group::CheckPosition(Vector2D pos1, Vector2D pos2) {
        bool result = false;
        for(auto& el: _elements){
            if(el->CheckPosition(pos1, pos2))
                result = true;
            if(result)
                break;
        }
        return result;
    }

    std::vector<Element *> Group::FindElements(Vector2D p1, Vector2D p2, std::vector<Element *> &elements) {
        std::vector<Element *> result, changedElements;

        for(auto el = elements.begin(); el != elements.end(); el++) {
            if((*el)->CheckPosition(p1, p2)) {
                ElementsHistory::otherPos.push_back(el - elements.begin());
            }
        }

        for(auto& el: elements)
            if(el->CheckPosition(p1, p2)) {
                result.push_back(el);
                ReplacePointer(el, elements);
            }
            else changedElements.push_back(el);

        elements = changedElements;

        return result;
    }

    Element *Group::FindElement(Vector2D point, std::vector<Element *> &elements) {
        Element* result = nullptr;
        bool isFirst = true;

        for(auto& el: elements)
            if(isFirst && el->CheckPosition({point.x + WORKSPACE_X_ST, point.y + WORKSPACE_Y_ST})) {
                result = el;
                isFirst = false;
            }

        return result;
    }

    Vector2D Group::FindCorrectPos(Vector2D p1, Vector2D p2) {
        Vector2D pos = p1;

        if(p2.x < pos.x)
            pos.x = p2.x;
        if(p2.y < pos.y)
            pos.y = p2.y;

        return pos;
    }

    Vector2D Group::FindSize(Vector2D p1, Vector2D p2) {
        Vector2D result;

        result = {(p1.x > p2.x ? p1.x - p2.x : p2.x - p1.x),
                  (p1.y > p2.y ? p1.y - p2.y : p2.y - p1.y)};

        return result;
    }

    void Group::SetSize(Vector2D size) {
        _size = size;
    }

    void Group::SetElements(std::vector<Element *> &elements) {
        _elements.clear();
        _elementsPos.clear();
        for(Element* el: elements) {
            Element* buf = FigureBuilder::ConvertChildClass(el);
            if(buf) {
                _elements.push_back(buf);
            }
        }
        {
            Vector2D buf;
            for (auto &el: _elements) {
                buf = el->GetPos();
                _elementsPos.push_back({buf.x - _pos.x, buf.y - _pos.y});
            }
        }
        _nextElement = nullptr;
    }

    void Group::AddElement(Element *el) {
        _elements.push_back(el);
        auto buf = el->GetPos();
        _elementsPos.push_back({buf.x - _pos.x, buf.y - _pos.y});
    }

    bool Group::operator==(Element *element) {
        return Element::operator==(element)
        && _size.x == reinterpret_cast<Group*>(element)->_size.x
        && _size.y == reinterpret_cast<Group*>(element)->_size.y
        && _elements.size() == reinterpret_cast<Group*>(element)->_elements.size();
    }

    Group &Group::operator=(Element *element) {
        Element::operator=(element);
        _size = reinterpret_cast<Group*>(element)->_size;
        ClearElements();
        for(Element* el: reinterpret_cast<Group*>(element)->_elements) {
            Element* buf = FigureBuilder::ConvertChildClass(el);
            if(buf) {
                _elements.push_back(buf);
            }
        }
        for(Vector2D el: reinterpret_cast<Group*>(element)->_elementsPos)
            _elementsPos.push_back(el);
        return *this;
    }

    Group::~Group() {
        ClearElements();
    }

    void Group::ClearElements() {
        for(Element* el: _elements)
            delete el;
        _elements.clear();
        _elementsPos.clear();
    }

    std::string Group::GetTextData(Vector2D* pos, bool needPos, bool needColor) {
        std::string result("Group ");
        static Vector2D vec;
        if(pos)
            result += Element::GetTextData(pos, needColor, needColor) + "{";
        else result += Element::GetTextData(nullptr, needColor, needColor) + "{";
        int counter = 0;
        for(auto& el: _elements) {
            if(pos) {
                vec = {pos->x + _elementsPos[counter].x, pos->y + _elementsPos[counter].y};
                result += "\n\t" + el->GetTextData(&vec);
            }
            else {
                vec = {_pos.x + _elementsPos[counter].x, _pos.y + _elementsPos[counter].y};
                result += "\n\t" + el->GetTextData(&vec);
            }
            counter++;
        }
        result += "}";
        return result;
    }
} // l5