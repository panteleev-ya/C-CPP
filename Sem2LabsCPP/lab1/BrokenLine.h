#ifndef CLION_BROKENLINE_H
#define CLION_BROKENLINE_H

#include <type_traits>
#include <vector>
#include <cmath>
#include "Point.h"

using std::vector;

template <class T, class=std::enable_if_t<isNumeric<T>>>
class BrokenLine {
public:
    BrokenLine() = default;
    explicit BrokenLine(vector<Point<T>> points) : _points(points) {

    }
    BrokenLine(const BrokenLine& obj) : _points(obj._points) {

    }

    [[nodiscard]] double perimeter() const {
        double result = 0.0;
        for (size_t i = 1; i < _points.size(); i++) {
            result += pointsDistance(_points[i], _points[i - 1]);
        }
        return result;
    }
private:
    vector<Point<T>> _points;
};


#endif //CLION_BROKENLINE_H
