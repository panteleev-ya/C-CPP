#ifndef CLION_TRAPEZOID_H
#define CLION_TRAPEZOID_H

#include "Polygon.h"

template <class T, class=std::enable_if_t<isNumeric<T>>>
class Trapezoid : public Polygon<T> {
public:
    Trapezoid() = default;
    explicit Trapezoid(vector<Point<T>> points) {
        for (size_t i = 0; i < 4; i++) {
            this->points.push_back(points[i]);
        }
    }
    bool isValid() {
        vector<Point<T>> vectors;
        for (size_t i = 1; i < 4; i++) {
            vectors.push_back(Point<T>(this->points[i].getX() - this->points[i - 1].getX(),
                                       this->points[i].getY() - this->points[i - 1].getY()));
        }
        vectors.push_back(Point<T>(this->points[0].getX() - this->points[3].getX(),
                                   this->points[0].getY() - this->points[3].getY()));
        // Проверяем что (v1 параллельно v3) XOR (v2 параллельно v4)
        return isParallel(vectors[0], vectors[2]) ^ isParallel(vectors[1], vectors[3]);
    }

private:
    // Если либо Х, либо Y в обоих векторах равен 0 - параллельны
    // Если х2/x1 == y2/y1 - параллельны
    bool isParallel(Point<T> v1, Point<T> v2) {
        return v1.getX() == 0 && v2.getX() == 0 ||
               v1.getY() == 0 && v2.getY() == 0 ||
               v1.getX() / v2.getX() == v1.getY() / v2.getY();
    }
};

// (0, 0) -> (1, 1); (1, 1)
// (1, 0) -> (3, 2); (2, 2)

#endif //CLION_TRAPEZOID_H
