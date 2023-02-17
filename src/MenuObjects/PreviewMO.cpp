//
// Created by colte on 16.02.2023.
//

#include "PreviewMO.h"

namespace l5 {
    PreviewMO::PreviewMO(const FigureBuilder* builder, int size, bool needFrame)
    : MenuObject(size, 3), _builder(builder), _needFrame(needFrame) {}

    void PreviewMO::Draw(Vector2D pos) {
        Vector2D buf = {pos.x + GetLength()/2 + 25, pos.y + GetLength()/2};
        if(_needFrame)
            DrawRectangleLinesEx({pos.x + 25, pos.y + 15, static_cast<float>(GetLength()), static_cast<float>(GetLength())}, 2, BLACK);
        _builder->Draw(&buf);
    }

    void PreviewMO::Update(Vector2 pos) {

    }
} // l5