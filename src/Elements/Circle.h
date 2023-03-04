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
        Circle(Vector2D pos, int radius, ColorSt ColorSt, int thickness);
        Circle(Vector2D pos, int radius, ColorSt color);
        Circle(Circle& circle);
        Circle(Circle* circle);
        bool operator==(Element* element) override;
        Circle& operator=(Element* element) override;
        ~Circle() override = default;
        void Draw(Vector2D* pos = nullptr) override;
        bool CheckPosition(Vector2D mouse, Vector2D* pos = nullptr) override;
        bool CheckPosition(Vector2D pos1, Vector2D pos2) override;
        std::string GetTextData(Vector2D* pos = nullptr, bool needPos = true, bool needColor = true) override;

        // Finds closest value to given range.
        static int ClosestValue(int p, int x1, int x2);
        int* GetRadiusP();
        int* GetThicknessP();
    };

} // l5

#endif //LAB5_CIRCLE_H
