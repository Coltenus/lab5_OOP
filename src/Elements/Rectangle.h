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
        Rectangle(Vector2D pos, Vector2D size, ColorSt color, int thickness);
        Rectangle(Vector2D pos, Vector2D size, ColorSt color);
        Rectangle(Rectangle& rectangle);
        Rectangle(Rectangle* rectangle);
        bool operator==(Element* element) override;
        Rectangle& operator=(Element* element) override;
        ~Rectangle() override = default;
        void Draw(Vector2D* pos = nullptr) override;
        bool CheckPosition(Vector2D mouse, Vector2D* pos = nullptr) override;
        bool CheckPosition(Vector2D pos1, Vector2D pos2) override;
        std::string GetTextData(Vector2D* pos = nullptr, bool needPos = true, bool needColor = true) override;

        float* GetSizeXP();
        float* GetSizeYP();
        int* GetThickness();
    };

} // l5

#endif //LAB5_RECTANGLE_H
