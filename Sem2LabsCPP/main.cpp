#include <iostream>
#include "Point.h"
#include "BrokenLine.h"
#include "Polygon.h"
#include "RegularPolygon.h"
#include "Trapezoid.h"
#include "Triangle.h"

using std::cin;
using std::cout;

int main() {
    vector<Point<int>> points = { Point(0, 0),
                             Point(0, 1),
                             Point(1, 1),
                             Point(1, 0)};
    vector<Point<int>> pointsTrapezoid = { Point(0, 0),
                                  Point(1, 1),
                                  Point(1, 3),
                                  Point(0, 4)};
    BrokenLine<int> brokenLine(points);
    cout << "BrokenLine Perimeter: " << brokenLine.perimeter() << '\n';

    Polygon<int> polygon(points);
    cout << "Polygon Perimeter: " << polygon.perimeter() << '\n';
    cout << "Polygon Area: " <<  polygon.area() << '\n';

    Triangle<int> triangle(points);
    cout << "Triangle Perimeter: " << triangle.perimeter() << '\n';
    cout << "Triangle Area: " << triangle.area() << '\n';

    Trapezoid<int> trapezoid(pointsTrapezoid);
    cout << "Trapezoid Perimeter: " << trapezoid.perimeter() << '\n';
    cout << "Trapezoid Area: " << trapezoid.area() << '\n';
    cout << "Trapezoid isValid(): " << trapezoid.isValid() << '\n';
    cout << "Square is not Trapezoid: " << Trapezoid<int>(points).isValid() << '\n';

    RegularPolygon<int> regularPolygon(points);
    cout << "RegularPolygon Perimeter: " << regularPolygon.perimeter() << '\n';
    cout << "RegularPolygon Area: " << regularPolygon.area() << '\n';
    cout << "RegularPolygon isValid(): " << regularPolygon.isValid() << '\n';
    cout << "Trapezoid is not RegularPolygon: " << RegularPolygon<int>(pointsTrapezoid).isValid() << '\n';
    return 0;
}
