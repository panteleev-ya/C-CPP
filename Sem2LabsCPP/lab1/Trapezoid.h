#ifndef CLION_TRAPEZOID_H
#define CLION_TRAPEZOID_H

#include "Polygon.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class Trapezoid : public Polygon<T> {
public:
    Trapezoid() = default;
    explicit Trapezoid(vector<Point<T>> points) {
        size_t min_size = std::min(4, static_cast<int>(points.size()));
        for (size_t i = 0; i < min_size; i++) {
            this->_points.push_back(points[i]);
        }
        for (size_t i = min_size; i < 4; i++) {
            this->_points.push_back(points[0]);
        }
    }
    [[nodiscard]] bool isValid() const {
        vector<Point<T>> vectors;
        for (size_t i = 1; i < 4; i++) {
            Point<T> left = this->_points[i];
            Point<T> right = this->_points[i - 1];
            Point<T> p = left - right;
            vectors.push_back(p);
        }
        vectors.push_back(this->_points[0] - this->_points[3]);
        // Проверяем что (v1 параллельно v3) XOR (v2 параллельно v4)
        return isParallel(vectors[0], vectors[2]) ^ isParallel(vectors[1], vectors[3]);
    }

private:
    // Если либо Х, либо Y в обоих векторах равен 0 - параллельны
    // Если х2/x1 == y2/y1 - параллельны
    bool isParallel(Point<T> v1, Point<T> v2) const {
        return v1.getX() == 0 && v2.getX() == 0 ||
               v1.getY() == 0 && v2.getY() == 0 ||
               v1.getX() / v2.getX() == v1.getY() / v2.getY();
    }
};

// (0, 0) -> (1, 1); (1, 1)
// (1, 0) -> (3, 2); (2, 2)

#endif //CLION_TRAPEZOID_H
