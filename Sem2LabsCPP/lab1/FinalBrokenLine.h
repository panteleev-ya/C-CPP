#ifndef CLION_FINALBROKENLINE_H
#define CLION_FINALBROKENLINE_H

#include "BrokenLine.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class FinalBrokenLine {
public:
    FinalBrokenLine() = default;
    explicit FinalBrokenLine(vector<Point<T>> points) : _points(points) {

    }
    [[nodiscard]] virtual double perimeter() const {
        double result = 0.0;
        for (size_t i = 1; i < _points.size(); i++) {
            result += pointsDistance(_points[i], _points[i - 1]);
        }
        result += pointsDistance(_points[_points.size() - 1], _points[0]);
        return result;
    }

protected:
    vector<Point<T>> _points;
};


#endif //CLION_FINALBROKENLINE_H
