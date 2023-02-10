//
// Created by colte on 10.02.2023.
//

#ifndef LAB5_RECTANGLE_H
#define LAB5_RECTANGLE_H

#include "Element.h"

namespace l5 {

    class Rectangle : public Element {
    private:
        Vector2D _size;
        int _thickness;

    public:
        /*
         * Constructor with chosen thickness
         */
        Rectangle(Vector2D pos, Vector2D size, Color color, int thickness);
        /*
         * Constructor with thickness with value 1
         */
        Rectangle(Vector2D pos, Vector2D size, Color color);
        ~Rectangle() override = default;
        /*
         * Draw this rectangle on window
         * If position is not null, then circle will be drawn there
         */
        void Draw(Vector2D* pos = nullptr) override;
        /*
         * Check if a mouse clicked on the rectangle
         */
        bool CheckPosition(Vector2D pos) override;
        /*
         * Check if the rectangle is inside given area
         */
        bool CheckPosition(Vector2D pos1, Vector2D pos2) override;
    };

} // l5

#endif //LAB5_RECTANGLE_H
