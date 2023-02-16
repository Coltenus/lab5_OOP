//
// Created by colte on 10.02.2023.
//

#include "Group.h"
#include "elements.h"
#include <raylib.h>

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
            Element* buf = ConvertChildClass(el);
            if(buf) {
                _elements.push_back(buf);
            }
        }
    }

    Group::Group(Group *group)
    : Element(group), _size(group->_size), _elementsPos(group->_elementsPos) {
        for(Element* el: group->_elements) {
            Element* buf = ConvertChildClass(el);
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

        for(auto& el: elements)
            if(el->CheckPosition(p1, p2))
                result.push_back(el);
            else changedElements.push_back(el);

        elements = changedElements;

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
            Element* buf = ConvertChildClass(el);
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
    }

    Element *Group::ConvertChildClass(Element *element) {
        Element* buf = nullptr;
        switch (element->GetType()) {
            case 1:
                buf = new Circle(reinterpret_cast<Circle*>(element));
                break;
            case 2:
                buf = new Rectangle(reinterpret_cast<Rectangle*>(element));
                break;
            case 3:
                buf = new Group(reinterpret_cast<Group*>(element));
                break;
        }
        return buf;
    }
} // l5