//
// Created by colte on 16.02.2023.
//

#ifndef LAB5_PREVIEWMO_H
#define LAB5_PREVIEWMO_H

#include "MenuObject.h"
#include "../FigureBuilder.h"

namespace l5 {

    class PreviewMO : public MenuObject {
    private:
        const FigureBuilder* _builder;
        bool _needFrame;

    public:
        PreviewMO(const FigureBuilder* builder, int size, bool needFrame = false);
        ~PreviewMO() override = default;
        void Draw(Vector2D pos) override;
        void Update(Vector2 pos) override;
    };

} // l5

#endif //LAB5_PREVIEWMO_H
