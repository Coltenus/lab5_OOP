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
        /*
         * This constructor has argument "elements" which is contains elements in selected area
         */
        Group(Vector2D pos, Vector2D size, std::vector<Element*> elements);
        ~Group() override = default;
        /*
         * Draw this group on window
         * If position is not null, then circle will be drawn there
         */
        void Draw(Vector2D* pos = nullptr) override;
        /*
         * Check if a mouse clicked on the group
         */
        bool CheckPosition(Vector2D pos) override;
        /*
         * Check if the group is inside given area
         */
        bool CheckPosition(Vector2D pos1, Vector2D pos2) override;
    };

} // l5

#endif //LAB5_GROUP_H
