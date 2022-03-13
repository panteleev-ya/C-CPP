#ifndef CLION_REGULARPOLYGON_H
#define CLION_REGULARPOLYGON_H

#include "Polygon.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class RegularPolygon : public Polygon<T> {
public:
    RegularPolygon() = default;
    explicit RegularPolygon(vector<Point<T>> points) {
        this->points = points;
    }
    T perimeter() override {
        return pointsDistance(this->points[1], this->points[0]) * this->points.size();
    }
    bool isValid() {
        T distance = pointsDistance(this->points[0], this->points[this->points.size() - 1]);
        for (size_t i = 1; i < this->points.size(); i++) {
            if (distance != pointsDistance(this->points[i], this->points[i - 1])) {
                return false;
            }
        }
        return true;
    }
};


#endif //CLION_REGULARPOLYGON_H
