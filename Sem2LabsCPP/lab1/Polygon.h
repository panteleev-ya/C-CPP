#ifndef CLION_POLYGON_H
#define CLION_POLYGON_H

#include "FinalBrokenLine.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class Polygon : public FinalBrokenLine<T> {
public:
    Polygon() = default;
    explicit Polygon(vector<Point<T>> points){
        this->_points = points;
    }

    [[nodiscard]] double area() const {
        T x1 = this->_points[0].getX();
        T y1 = this->_points[0].getY();
        T x2, y2;
        double sum = 0.0;
        for (size_t i = 1; i < this->_points.size(); i++) {
            x2 = this->_points[i].getX();
            y2 = this->_points[i].getY();
//            sum += static_cast<double>((x1 + x2) * (y2 - y1));
            sum += static_cast<double>((x1 + x2) * (y2 - y1) / 2.0);
            x1 = x2;
            y1 = y2;
        }
//        sum += static_cast<double>((_points[0].getX() + x2) * (_points[0].getY() - y2));
        sum += static_cast<double>((this->_points[0].getX() + x2) * (this->_points[0].getY() - y2)  / 2.0);
//        sum = std::abs(sum) / 2.0;
        sum = std::abs(sum);
        return sum;
    }
};


#endif //CLION_POLYGON_H
