//
// Created by colte on 01.03.2023.
//

#include "ElementsHistory.h"
#include "FigureBuilder.h"

namespace l5 {
    ElementsHistory::ElementsHistory(std::vector<Element *> &vec) : _real(&vec),
    _buffer(nullptr) {
        FillCurrent();
    }

    ElementsHistory::~ElementsHistory() {
        ClearCurrent();
        ClearUndo();
        ClearRedo();
    }

    bool ElementsHistory::Check() {
        bool result = false;
        int counter = 0;

        if(_current.size() == _real->size() && _current.size() > 0){
            for(counter = 0; counter<_real->size(); counter++) {
                if(!(*_current[counter] == (*_real)[counter]))
                    break;
            }
            if(counter != _current.size()){
                opcode = Change;
                firstPos = counter;
            }
        }
        if(opcode != None)
            result = true;

        return result;
    }

    void ElementsHistory::AddState() {
        if(opcode != None) {
            _buffer = new OperationData;
            _buffer->opcode = opcode;
            switch (opcode) {
                case Add:
                    _buffer->fPos = firstPos;
                    _buffer->fElement = nullptr;
                    break;
                case Remove:
                case Change:
                    _buffer->fPos = firstPos;
                    _buffer->fElement = FigureBuilder::ConvertChildClass(_current[firstPos]);
                    break;
                case Disassemble:
                    _buffer->fPos = firstPos;
                    _buffer->fElement = FigureBuilder::ConvertChildClass(_current[firstPos]);
                    for(auto& el: otherPos)
                        _buffer->otherElements.emplace_back(el, nullptr);
                    break;
                case Assemble:
                    _buffer->fPos = firstPos;
                    _buffer->fElement = nullptr;
                    for(auto& el: otherPos)
                        _buffer->otherElements.emplace_back(el, FigureBuilder::ConvertChildClass(_current[el]));
                    break;
                case AddToGroup:
                    _buffer->fPos = firstPos;
                    _buffer->fElement = FigureBuilder::ConvertChildClass(_current[firstPos]);
                    _buffer->otherElements.emplace_back(otherPos[0], FigureBuilder::ConvertChildClass(_current[otherPos[0]]));
                    break;
                case RemFromGroup:
                    _buffer->fPos = firstPos;
                    _buffer->fElement = FigureBuilder::ConvertChildClass(_current[firstPos]);
                    _buffer->otherElements.emplace_back(otherPos[0], nullptr);
                    break;
            }
            ClearCurrent();
            FillCurrent();
            opcode = None;
            firstPos = -1;
            otherPos.clear();
        }
    }

    void ElementsHistory::AddUndo() {
        AddState();
        if(_buffer) {
            _undo.push(*_buffer);
            delete _buffer;
            _buffer = nullptr;
        }
        ClearRedo();
    }

    void ElementsHistory::AddRedo() {
        AddState();
        if(_buffer) {
            _redo.push(*_buffer);
            delete _buffer;
            _buffer = nullptr;
        }
    }

    void ElementsHistory::FillCurrent() {
        for(Element* el: *_real) {
            Element* buf = FigureBuilder::ConvertChildClass(el);
            if(buf) {
                _current.push_back(buf);
            }
        }
    }

    void ElementsHistory::ClearCurrent() {
        for(Element* el: _current)
            delete el;
        _current.clear();
    }

    void ElementsHistory::ReplaceState() {
        auto buf = *_buffer;
        _buffer = new OperationData;
        switch (buf.opcode) {
            case Add:
                _buffer->opcode = Remove;
                _buffer->fPos = buf.fPos;
                _buffer->fElement = FigureBuilder::ConvertChildClass(_current[buf.fPos]);
                if((*_real)[buf.fPos] == Element::lastElement)
                    Element::lastElement = nullptr;
                delete (*(_real->begin() + buf.fPos));
                _real->erase(_real->begin()+buf.fPos);
                break;
            case Remove:
                _buffer->opcode = Add;
                _buffer->fPos = buf.fPos;
                _buffer->fElement = nullptr;
                _real->insert(_real->begin()+buf.fPos, buf.fElement);
                Element::InsertPointer(*_real, buf.fPos);
                break;
            case Change:
                _buffer->opcode = Change;
                _buffer->fPos = buf.fPos;
                _buffer->fElement = FigureBuilder::ConvertChildClass(_current[buf.fPos]);
                *(*_real)[buf.fPos] = FigureBuilder::ConvertChildClass(buf.fElement);
                delete buf.fElement;
                break;
            case Assemble:
                _buffer->opcode = Disassemble;
                _buffer->fPos = buf.fPos;
                _buffer->fElement = FigureBuilder::ConvertChildClass(_current[buf.fPos]);
                if((*_real)[buf.fPos] == Element::lastElement)
                    Element::lastElement = nullptr;
                delete (*(_real->begin() + buf.fPos));
                _real->erase(_real->begin()+buf.fPos);
                for(auto& el: buf.otherElements){
                    _real->insert(_real->begin() + el.first, FigureBuilder::ConvertChildClass(el.second));
                    _buffer->otherElements.emplace_back(el.first, nullptr);
                    delete el.second;
                }
                break;
            case Disassemble:
                _buffer->opcode = Assemble;
                _buffer->fPos = buf.fPos;
                _buffer->fElement = nullptr;
                {
                    auto el = buf.otherElements.end();
                    while (el != buf.otherElements.begin()){
                        el--;
                        _buffer->otherElements.emplace_back((*el).first,
                                                            FigureBuilder::ConvertChildClass(_current[(*el).first]));
                        delete (*(_real->begin() + (*el).first));
                        _real->erase(_real->begin() + (*el).first);
                    }
                }
                {
                    auto other = _buffer->otherElements;
                    _buffer->otherElements.clear();
                    auto el = other.end();
                    while (el != other.begin()){
                        el--;
                        _buffer->otherElements.emplace_back(*el);
                    }
                }
                _real->insert(_real->begin()+buf.fPos, FigureBuilder::ConvertChildClass(buf.fElement));
                delete buf.fElement;
                Element::ReplacePointer((*(_real->begin()+buf.fPos)), *_real);
                break;
            case AddToGroup:
                _buffer->opcode = RemFromGroup;
                _buffer->fPos = buf.fPos;
                _buffer->fElement = FigureBuilder::ConvertChildClass(_current[buf.fPos]);
                _buffer->otherElements.emplace_back(buf.otherElements[0].first, nullptr);
                *(*_real)[buf.fPos] = FigureBuilder::ConvertChildClass(buf.fElement);
                delete buf.fElement;
                _real->insert(_real->begin() + buf.otherElements[0].first,
                              FigureBuilder::ConvertChildClass(buf.otherElements[0].second));
                Element::InsertPointer(*_real, buf.otherElements[0].first);
                delete buf.otherElements[0].second;
                break;
            case RemFromGroup:
                _buffer->opcode = AddToGroup;
                _buffer->fPos = buf.fPos;
                _buffer->fElement = FigureBuilder::ConvertChildClass(_current[buf.fPos]);
                *(*_real)[buf.fPos] = FigureBuilder::ConvertChildClass(buf.fElement);
                delete buf.fElement;
                _buffer->otherElements.emplace_back(buf.otherElements[0].first,
                                                    FigureBuilder::ConvertChildClass(_current[buf.otherElements[0].first]));
                delete (*(_real->begin() + buf.otherElements[0].first));
                _real->erase(_real->begin() + buf.otherElements[0].first);
                break;
            case None:
                break;
        }
        ClearCurrent();
        FillCurrent();
    }

    void ElementsHistory::ClearTop(int stackType) {
        if(stackType == 1) {
            _redo.pop();
        }
        else {
            _undo.pop();
        }
    }

    void ElementsHistory::Undo() {
        if(!_undo.empty()){
            _buffer = &_undo.top();
            ReplaceState();
            ClearTop(0);
            _redo.push(*_buffer);
            delete _buffer;
            _buffer = nullptr;
        }
    }

    void ElementsHistory::Redo() {
        if(!_redo.empty()){
            _buffer = &_redo.top();
            ReplaceState();
            ClearTop(1);
            _undo.push(*_buffer);
            delete _buffer;
            _buffer = nullptr;
        }
    }

    void ElementsHistory::ClearRedo() {
        while (!_redo.empty()) {
            if(!_redo.top().fElement) {
                delete _redo.top().fElement;
                _redo.top().fElement = nullptr;
            }
            if(!_redo.top().otherElements.empty()) {
                for(auto& el: _redo.top().otherElements)
                    delete el.second;
            }
            _redo.pop();
        }
    }

    void ElementsHistory::ClearUndo() {
        while (!_undo.empty()) {
            if(!_undo.top().fElement) {
                delete _undo.top().fElement;
                _undo.top().fElement = nullptr;
            }
            if(!_undo.top().otherElements.empty()) {
                for(auto& el: _undo.top().otherElements)
                    delete el.second;
            }
            _undo.pop();
        }
    }

    void ElementsHistory::Clear() {
        ClearCurrent();
        ClearUndo();
        ClearRedo();
        FillCurrent();
    }
} // l5