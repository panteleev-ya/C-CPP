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
        this->x = x;
        this->y = y;
    }
    Point(Point const &obj) {
        this->x = obj.x;
        this->y = obj.y;
    }
    T getX() {
        return x;
    }
    T getY() {
        return y;
    }
private:
    T x = 0;
    T y = 0;
};

template <class T, class=std::enable_if_t<isNumeric<T>>>
T pointsDistance(Point<T> p1, Point<T> p2) {
    T xLen = p2.getX() - p1.getX();
    T yLen = p2.getY() - p1.getY();
    return sqrt(static_cast<double>(xLen * xLen + yLen * yLen));
}

#endif //CLION_POINT_H
