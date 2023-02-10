//
// Created by colte on 10.02.2023.
//

#include "Circle.h"
#include <raylib.h>
#include <valarray>

namespace l5 {
    Circle::Circle(Vector2D pos, int radius, Color color, int thickness)
    : Element(pos, color), _radius(radius) {
        if(thickness > _radius)
            _thickness = _radius;
        else _thickness = thickness;
    }

    Circle::Circle(Vector2D pos, int radius, Color color)
    : Circle(pos, radius, color, 1) {}

    void Circle::Draw(Vector2D* pos) {
        static int counter;
        counter = _radius;
        do {
            if(pos == nullptr)
                DrawCircleLines(_pos.x, _pos.y, counter, {_color.r, _color.g, _color.b, _color.a});
            else DrawCircleLines(pos->x, pos->y, counter, {_color.r, _color.g, _color.b, _color.a});
            counter--;
        } while (counter > _radius - _thickness);
    }

    bool Circle::CheckPosition(Vector2D pos) {
        return pow(_pos.x - pos.x, 2) + pow(_pos.y - pos.y, 2) <= pow(_radius, 2);
    }

    bool Circle::CheckPosition(Vector2D pos1, Vector2D pos2) {
        int x, y, distance;
        if(pos1.x >= pos2.x) {
            x = ClosestValue(_pos.x, pos2.x, pos1.x);
        } else {
            x = ClosestValue(_pos.x, pos1.x, pos2.x);
        }
        if(pos1.y >= pos2.y) {
            y = ClosestValue(_pos.y, pos2.y, pos1.y);
        } else {
            y = ClosestValue(_pos.y, pos1.y, pos2.y);
        }
        distance = sqrt(pow(_pos.x - x, 2) + pow(_pos.y - y, 2));

        if(distance <= _radius)
            return true;
        else return false;
    }

    int Circle::ClosestValue(int p, int x1, int x2) {
        if(p < x1)
            return x1;
        else if(p > x2)
            return x2;
        else return p;
    }
} // l5