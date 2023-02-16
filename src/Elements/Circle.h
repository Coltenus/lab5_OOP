//
// Created by colte on 10.02.2023.
//

#ifndef LAB5_CIRCLE_H
#define LAB5_CIRCLE_H

#include "Element.h"

namespace l5 {

    class Circle : public Element {
    private:
        int _radius, _thickness;

    public:
        /*
         * Constructor with chosen thickness
         */
        Circle(Vector2D pos, int radius, ColorSt ColorSt, int thickness);
        /*
         * Constructor with thickness with value 1
         */
        Circle(Vector2D pos, int radius, ColorSt color);
        ~Circle() override = default;
        /*
         * Draw this circle on window
         * If position is not null, then the circle will be drawn there
         */
        void Draw(Vector2D* pos = nullptr) override;
        /*
         * Check if a mouse clicked on the circle
         */
        bool CheckPosition(Vector2D pos) override;
        /*
         * Check if the circle is inside given area
         */
        bool CheckPosition(Vector2D pos1, Vector2D pos2) override;
        /*
         * Find closest value inside range between x1 and x2
         */
        static int ClosestValue(int p, int x1, int x2);
    };

} // l5

#endif //LAB5_CIRCLE_H
