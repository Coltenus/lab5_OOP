//
// Created by colte on 10.02.2023.
//

#ifndef LAB5_COMMON_H
#define LAB5_COMMON_H

namespace l5 {
    struct Vector2D {
        float x, y;
    };

    struct ColorSt {
        unsigned char r, g, b, a;
    };

#define WIDTH 1600
#define HEIGHT 900
#define WORKSPACE_X_ST 0
#define WORKSPACE_X_END (WIDTH - 300)
#define WORKSPACE_Y_ST 40
#define WORKSPACE_Y_END HEIGHT
}

#endif //LAB5_COMMON_H
