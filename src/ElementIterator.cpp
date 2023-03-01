//
// Created by colte on 01.03.2023.
//

#include "ElementIterator.h"

namespace l5 {
    ElementIterator::ElementIterator(std::vector<Element *> &vec, bool reset) : _canBeReset(reset) {
        _elements = &vec;
        _currentElement = nullptr;
    }

    Element *ElementIterator::GetCurrentElement() {
        return _currentElement;
    }

    Element *ElementIterator::NextElement(bool isCycled) {
        if(_canBeReset && resetValues) {
            _currentElement = nullptr;
            resetValues = false;
        }
        if(_currentElement)
            _currentElement->HandleElementSelection();
        if(IsEnd(isCycled)) {
            _currentElement = *_elements->begin();
            if(!isCycled) {
                _currentElement->SelectionActivate();
            }
        }
        else {
            _currentElement = _currentElement->_nextElement;
            if(_currentElement)
                _currentElement->SelectionActivate();
            if(!isCycled && !_currentElement) {
                Element::HandleSelection();
            }
        }
        return _currentElement;
    }

    bool ElementIterator::IsEnd(bool isCycled) {
        if(isCycled) {
            return _currentElement->_nextElement == nullptr;
        }
        else return _currentElement == nullptr;
    }
} // l5