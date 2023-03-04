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
        // Finds elements within area.
        static std::vector<Element*> FindElements(Vector2D p1, Vector2D p2, std::vector<Element*>& elements);
        // Finds first element in given point.
        static Element* FindElement(Vector2D point, std::vector<Element*>& elements);
        // Finds correct point where will be located upper left corner of group.
        static Vector2D FindCorrectPos(Vector2D p1, Vector2D p2);
        // Find correct size of group.
        static Vector2D FindSize(Vector2D p1, Vector2D p2);

        Group(Vector2D pos, Vector2D size, std::vector<Element*>& elements);
        Group(Group& group);
        Group(Group* group);
        bool operator==(Element* element) override;
        Group& operator=(Element* element) override;
        ~Group() override;
        void Draw(Vector2D* pos = nullptr) override;
        bool CheckPosition(Vector2D mouse, Vector2D* pos = nullptr) override;
        bool CheckPosition(Vector2D pos1, Vector2D pos2) override;
        std::string GetTextData(Vector2D* pos = nullptr, bool needPos = false, bool needColor = false) override;

        void SetSize(Vector2D size);
        void SetElements(std::vector<Element*>& elements);
        void AddElement(Element*);
        void ClearElements();
    };

} // l5

#endif //LAB5_GROUP_H
