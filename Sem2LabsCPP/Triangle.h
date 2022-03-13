#ifndef CLION_TRIANGLE_H
#define CLION_TRIANGLE_H

#include "Polygon.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class Triangle : public Polygon<T> {
public:
    Triangle() = default;
    explicit Triangle(vector<Point<T>> points) : Polygon<T>(){
        for (size_t i = 0; i < 3; i++) {
            this->points.push_back(points[i]);
        }
    }
    Triangle(Point<T> A, Point<T> B, Point<T> C) {
        this->points = { A, B, C };
    }
};


#endif //CLION_TRIANGLE_H
