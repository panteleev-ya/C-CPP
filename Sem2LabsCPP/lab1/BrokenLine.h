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
    explicit BrokenLine(vector<Point<T>> points) {
        this->points = points;
    }
    BrokenLine(const BrokenLine& obj) {
        this->points = obj.points;
    }

    T perimeter() {
        T result = static_cast<T>(0);
        for (size_t i = 1; i < points.size(); i++) {
            result += pointsDistance(points[i], points[i - 1]);
        }
        return result;
    }
private:
    vector<Point<T>> points;
};


#endif //CLION_BROKENLINE_H
