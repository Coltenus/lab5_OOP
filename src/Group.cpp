//
// Created by colte on 10.02.2023.
//

#include "Group.h"

namespace l5 {
    Group::Group(Vector2D pos, Vector2D size, std::vector<Element *> elements)
    : Element(pos, {0, 0, 0, 0}), _size(size), _elements(elements) {
        Vector2D buf;
        for(auto& el: _elements) {
            buf = el->GetPos();
            _elementsPos.push_back({buf.x - _pos.x, buf.y - _pos.y});
        }
    }

    void Group::Draw(Vector2D *pos) {
        static Vector2D vec;
        if(pos == nullptr) {
            for(int i = 0; i < _elements.size(); i++) {
                vec = _elementsPos[i];
                vec = {_pos.x + vec.x, _pos.y + vec.y};
                _elements[i]->Draw(&vec);
            }
        }
        else {
            for(int i = 0; i < _elements.size(); i++) {
                vec = _elementsPos[i];
                vec = {pos->x + vec.x, pos->y + vec.y};
                _elements[i]->Draw(&vec);
            }
        }
    }

    bool Group::CheckPosition(Vector2D pos) {
        bool result = false;
        for(auto& el: _elements){
            if(el->CheckPosition(pos))
                result = true;
            if(result)
                break;
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
} // l5