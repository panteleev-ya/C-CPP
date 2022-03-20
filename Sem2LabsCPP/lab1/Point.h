#ifndef CLION_POINT_H
#define CLION_POINT_H

#include <type_traits>
#include <cmath>

template<typename T>
constexpr bool isNumeric = std::is_same<T, int>::value
                           || std::is_same<T, double>::value
                           || std::is_same<T, long>::value
                           || std::is_same<T, long long>::value
                           || std::is_same<T, short>::value;

template <class T, class=std::enable_if_t<isNumeric<T>>>
class Point {
public:
    Point() = default;
    explicit Point(T x, T y) {
        this->_x = x;
        this->_y = y;
    }
    Point(Point const &obj) {
        this->_x = obj.getX();
        this->_y = obj.getY();
    }
    T getX() const {
        return _x;
    }
    T getY() const {
        return _y;
    }

    Point operator-(const Point& obj) const {
        T x = this->_x - obj.getX();
        T y = this->_y - obj.getY();
        Point p(x, y);
        return p;
    }
private:
    T _x = 0;
    T _y = 0;
};

template <class T, class=std::enable_if_t<isNumeric<T>>>
double pointsDistance(Point<T> p1, Point<T> p2) {
    double xLen = p2.getX() - p1.getX();
    double yLen = p2.getY() - p1.getY();
    return sqrt(static_cast<double>(xLen * xLen + yLen * yLen));
}

#endif //CLION_POINT_H
