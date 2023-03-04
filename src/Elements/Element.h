//
// Created by colte on 10.02.2023.
//

#ifndef LAB5_ELEMENT_H
#define LAB5_ELEMENT_H

#include "../common.h"
#include <vector>
#include <string>

namespace l5 {

    class Element {
    protected:
        int _type;
        Vector2D _pos;
        ColorSt _color;
        bool _isSelected, _needRemoval;
        Element *_nextElement, *_previousElement;

    public:
        static bool elementSelected, resetSelection;
        static Element *selectedElement, *lastElement;
        static void HandleSelection();
        static void ReplacePointer(Element* el, std::vector<Element*>& vec);
        static void InsertPointer(std::vector<Element*>& vec, int pos);
        Element(int type, Vector2D pos, ColorSt color);
        Element(Element& element);
        Element(Element* element);
        virtual bool operator==(Element* element);
        virtual Element& operator=(Element* element);
        virtual ~Element() = default;
        virtual void Draw(Vector2D* pos = nullptr) = 0;
        void Update();
        // Check if a mouse clicked on the element.
        virtual bool CheckPosition(Vector2D mouse, Vector2D* pos = nullptr) = 0;
        // Check if the element is inside given area.
        virtual bool CheckPosition(Vector2D pos1, Vector2D pos2) = 0;
        // Get element position
        Vector2D GetPos();
        void SetPos(Vector2D pos);
        // Sets flag to remove this element.
        void StartRemoval();
        // Returns flag to remove this element.
        bool NeedRemoval();
        int GetType();
        unsigned char* GetRedP();
        unsigned char* GetGreenP();
        unsigned char* GetBlueP();
        // Disable element selection.
        void HandleElementSelection(bool endSelection = true);
        void SelectionActivate();
        // Compares elements.
        bool IsSame(Element* element);
        virtual std::string GetTextData(Vector2D* pos = nullptr, bool needPos = true, bool needColor = true);
        // Sets pointers to created element.
        void SetPointer();

        friend class ElementIterator;
        friend class FigureBuilder;
        friend class ElementsHistory;
    };

} // l5

#endif //LAB5_ELEMENT_H
