//
// Created by colte on 01.03.2023.
//

#ifndef LAB5_ELEMENTITERATOR_H
#define LAB5_ELEMENTITERATOR_H

#include "Elements/Element.h"

namespace l5 {

    class ElementIterator {
    private:
        std::vector<Element*>* _elements;
        Element* _currentElement;
        bool _canBeReset;

    public:
        static bool resetValues;
        explicit ElementIterator(std::vector<Element*>& vec, bool reset = false);
        Element* GetCurrentElement();
        Element* NextElement(bool isCycled = false);
        Element* PreviousElement(bool isCycled = false);
        bool IsEndNext(bool isCycled = false);
        bool IsEndPrevious(bool isCycled = false);
    };

} // l5

#endif //LAB5_ELEMENTITERATOR_H
