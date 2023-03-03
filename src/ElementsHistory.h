//
// Created by colte on 01.03.2023.
//

#ifndef LAB5_ELEMENTSHISTORY_H
#define LAB5_ELEMENTSHISTORY_H

#include "Elements/Element.h"
#include <vector>
#include <stack>

namespace l5 {
    enum OpCode : unsigned char {
        None = 0,
        Add,
        Remove,
        Change,
        Assemble,
        Disassemble,
        AddToGroup,
        RemFromGroup
    };

    struct OperationData {
        OpCode opcode;
        int fPos;
        Element *fElement;
        std::vector<std::pair<int, Element*>> otherElements;
    };

    class ElementsHistory {
    private:
        std::vector<Element*> _current, *_real;
        std::stack<OperationData> _undo, _redo;
        OperationData* _buffer;
        void FillCurrent();
        void ClearCurrent();
        void ClearTop(int stackType = 0);

    public:
        static OpCode opcode;
        static int firstPos;
        static std::vector<int> otherPos;
        explicit ElementsHistory(std::vector<Element*>& vec);
        ~ElementsHistory();
        bool Check();
        void AddState();
        void AddUndo();
        void AddRedo();
        void Undo();
        void Redo();
        void ReplaceState();
        void ClearRedo();
        void ClearUndo();
        void Clear();
    };

} // l5

#endif //LAB5_ELEMENTSHISTORY_H
