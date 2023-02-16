//
// Created by colte on 15.02.2023.
//

#ifndef LAB5_MENUOBJECT_H
#define LAB5_MENUOBJECT_H

#include "../common.h"
#include <raylib.h>

namespace l5 {

    class MenuObject {
    private:
        int _length;
        int _offset[2];
        int _type;

    public:
        MenuObject(int length, int type) : _length(length), _type(type) {}
        MenuObject(int type) : MenuObject(0, type) {}
        MenuObject() : MenuObject(0, false) {}
        virtual ~MenuObject() = default;
        virtual void Draw(Vector2D pos) = 0;
        virtual void Update(Vector2 pos) = 0;
        int GetLength() { return _length; }
        void SetLength(int length) { _length = length; }
        int* GetOffset() { return _offset; }
        int GetType() { return _type; }
    };

} // l5

#endif //LAB5_MENUOBJECT_H
