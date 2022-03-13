#ifndef CLION_POLYGON_H
#define CLION_POLYGON_H

#include "BrokenLine.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class Polygon {
public:
    Polygon() = default;
    explicit Polygon(vector<Point<T>> points) {
        this->points = points;
    }
    virtual T perimeter() {
        T result = static_cast<T>(0);
        for (size_t i = 1; i < points.size(); i++) {
            result += pointsDistance(points[i], points[i - 1]);
        }
        result += pointsDistance(points[points.size() - 1], points[0]);
        return result;
    }
    double area() {
        T result = static_cast<T>(0);
        T x1 = points[0].getX();
        T y1 = points[0].getY();
        T x2, y2;
        double sum = 0.0;
        for (size_t i = 1; i < points.size(); i++) {
            x2 = points[i].getX();
            y2 = points[i].getY();
            sum += (x1 + x2) * (y2 - y1);
            x1 = x2;
            y1 = y2;
        }
        sum += (points[0].getX() + x2) * (points[0].getY() - y2);
        sum = std::abs(sum) / 2;
        return sum;
    }

protected:
    vector<Point<T>> points;
};


#endif //CLION_POLYGON_H
