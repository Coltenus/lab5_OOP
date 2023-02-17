//
// Created by colte on 16.02.2023.
//

#ifndef LAB5_FIGUREBUILDER_H
#define LAB5_FIGUREBUILDER_H

#include "Elements/elements.h"

namespace l5 {

    class FigureBuilder {
    private:
        Circle* _circle;
        Rectangle* _rectangle;
        Group* _group;

    public:
        int mode;
        FigureBuilder();
        ~FigureBuilder();
        Element* CreateFigure(Vector2D pos, std::vector<Element*>* elements = nullptr, Vector2D size = {0, 0});
        void Draw(Vector2D* pos) const;
        Circle* GetCircle();
        Rectangle* GetRectangle();
        Group* GetGroup();
    };

} // l5

#endif //LAB5_FIGUREBUILDER_H
