#ifndef CLION_REGULARPOLYGON_H
#define CLION_REGULARPOLYGON_H

#include "Polygon.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class RegularPolygon : public Polygon<T> {
public:
    RegularPolygon() = default;
    explicit RegularPolygon(vector<Point<T>> points) {
        this->_points = points;
    }
    [[nodiscard]] double perimeter() const override {
        return pointsDistance(this->_points[1], this->_points[0]) * this->_points.size();
    }
    [[nodiscard]] bool isValid() const {
        T distance = pointsDistance(this->_points[0], this->_points[this->_points.size() - 1]);
        for (size_t i = 1; i < this->_points.size(); i++) {
            if (distance != pointsDistance(this->_points[i], this->_points[i - 1])) {
                return false;
            }
        }
        return true;
    }
};


#endif //CLION_REGULARPOLYGON_H
