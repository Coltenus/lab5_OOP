//
// Created by colte on 10.02.2023.
//

#ifndef LAB5_GROUP_H
#define LAB5_GROUP_H

#include "Element.h"
#include <vector>

namespace l5 {

    class Group : public Element {
    private:
        Vector2D _size;
        std::vector<Element*> _elements;
        std::vector<Vector2D> _elementsPos;

    public:
        static bool firstPointSelected;
        static std::vector<Element*> FindElements(Vector2D p1, Vector2D p2, std::vector<Element*>& elements);
        static Element* FindElement(Vector2D p, std::vector<Element*>& elements);
        static Vector2D FindCorrectPos(Vector2D p1, Vector2D p2);
        static Vector2D FindSize(Vector2D p1, Vector2D p2);
        /*
         * This constructor has argument "elements" which is contains elements in selected area
         */
        Group(Vector2D pos, Vector2D size, std::vector<Element*>& elements);
        Group(Group& group);
        Group(Group* group);
        bool operator==(Element* element) override;
        Group& operator=(Element* element) override;
        ~Group() override;
        /*
         * Draw this group on window
         * If position is not null, then circle will be drawn there
         */
        void Draw(Vector2D* pos = nullptr) override;
        /*
         * Check if a mouse clicked on the group
         */
        bool CheckPosition(Vector2D mouse, Vector2D* pos = nullptr) override;
        /*
         * Check if the group is inside given area
         */
        bool CheckPosition(Vector2D pos1, Vector2D pos2) override;
        void SetSize(Vector2D size);
        void SetElements(std::vector<Element*>& elements);
        void AddElement(Element*);
        void ClearElements();
        std::string GetTextData(Vector2D* pos = nullptr, bool needPos = false, bool needColor = false) override;
    };

} // l5

#endif //LAB5_GROUP_H
