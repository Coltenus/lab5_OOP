//
// Created by colte on 10.02.2023.
//

#include "Circle.h"
#include <raylib.h>
#include <valarray>

namespace l5 {
    Circle::Circle(Vector2D pos, int radius, ColorSt color, int thickness)
    : Element(1, pos, color), _radius(radius) {
        if(thickness > _radius)
            _thickness = _radius;
        else _thickness = thickness;
    }

    Circle::Circle(Vector2D pos, int radius, ColorSt color)
    : Circle(pos, radius, color, 1) {}

    Circle::Circle(Circle &circle)
    : Element(circle), _radius(circle._radius), _thickness(circle._thickness) {}

    Circle::Circle(Circle *circle)
    : Element(circle), _radius(circle->_radius), _thickness(circle->_thickness) {}

    void Circle::Draw(Vector2D* pos) {
        static int counter;
        counter = _radius;
        if(_isSelected) _color.a = 120;
        else _color.a = 255;
        if(_thickness < _radius){
            do {
                if (pos == nullptr)
                    DrawCircleLines(_pos.x, _pos.y, counter, {_color.r, _color.g, _color.b, _color.a});
                else DrawCircleLines(pos->x, pos->y, counter, {_color.r, _color.g, _color.b, _color.a});
                counter--;
            } while (counter > _radius - _thickness);
        }
        else {
            if (pos == nullptr)
                DrawCircle(_pos.x, _pos.y, _radius, {_color.r, _color.g, _color.b, _color.a});
            else DrawCircle(pos->x, pos->y, _radius, {_color.r, _color.g, _color.b, _color.a});
        }
    }

    bool Circle::CheckPosition(Vector2D mouse, Vector2D* pos) {
        bool result;

        if(pos) result = pow(pos->x - mouse.x, 2) + pow(pos->y - mouse.y, 2) <= pow(_radius, 2);
        else result = pow(_pos.x - mouse.x, 2) + pow(_pos.y - mouse.y, 2) <= pow(_radius, 2);

        return result;
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

    int *Circle::GetRadiusP() {
        return &_radius;
    }

    int *Circle::GetThicknessP() {
        return &_thickness;
    }
} // l5