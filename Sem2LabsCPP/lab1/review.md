# Code Review (by Anuiel)
## Overall remarks
1. private members should be with underscore like ```_point```


## "BrokenLine.h"

No
```
explicit BrokenLine(vector<Point<T>> _points) {
    this->_points = _points;
}
BrokenLine(const BrokenLine& obj) {
    this->_points = obj._points;
}
```
Yes
```
explicit BrokenLine(vector<Point<T>> _points) _points(_points) {}
BrokenLine(const BrokenLine& obj) point(obj.point) {}
```


Type T as a return is questionable 
```
T perimeter() {
    T result = static_cast<T>(0);
    for (size_t i = 1; i < _points.size(); i++) {
        result += pointsDistance(_points[i], _points[i - 1]);
    }
    return result;
}
```


## "Point.h"

Not
```
explicit Point(T _x, T _y) {
    this->_x = _x;
    this->_y = _y;
}
Point(Point const &obj) {
    this->_x = obj._x;
    this->_y = obj._y;
}
```

but rather

```    
explicit Point(T _x, T _y) _x(_x), _y(_y) {}

Point(Point const &obj) _x(obj._x), _y(obj._y) {}
```

Type T as a return is questionable 
```
T pointsDistance(Point<T> p1, Point<T> p2) {
    T xLen = p2.getX() - p1.getX();
    T yLen = p2.getY() - p1.getY();
    return sqrt(static_cast<double>(xLen * xLen + yLen * yLen));
}
```

## "Polygin.h"

Not
```
explicit Polygon(vector<Point<T>> _points) {
    this->_points = _points;
}
```
But the
```
explicit Polygon(vector<Point<T>> _points) point(point) {}
```

Returning type is questionable
```
virtual T perimeter() {
    T result = static_cast<T>(0);
    for (size_t i = 1; i < _points.size(); i++) {
        result += pointsDistance(_points[i], _points[i - 1]);
    }
    result += pointsDistance(_points[_points.size() - 1], _points[0]);
    return result;
}
```

In ```area()```
```
sum += (x1 + x2) * (y2 - y1);
```
May be overflow

And area of polygon with integer point are integer or [half-integer](https://en.wikipedia.org/wiki/Half-integer), so double usage is questionable here too (from my point of view)

## "Polynomail.h"

All returning types should be ```Polynomial& ```, not ```Polynomial```

Bad
```
explicit Polynomial(vector<T> _coefficients) {
    this->_coefficients = _coefficients;
}
```

Good
```
explicit Polynomial(vector<T> _coefficients) _coefficients(_coefficients) {}
```

```
Polynomial operator++ ()
```
can looks like this

```
Polynomial operator++ () {
    for (auto &element : _coefficients) {
        ++element;
    }
    return *this;
}
```

The same applied to
```
Polynomial operator-- ()
```

```
Polynomial operator+
```
i would implemented like this

```
private:
    Polynomial(size_t size) : _coefficients(vector<T>(size, 0)) {}
    
public:
    Polynomial operator+ (const Polynomial &obj) {
        size_t size_min = std::min(_coefficients.size(), obj._coefficients.size());
        size_t size_max = std::max(_coefficients.size(), obj._coefficients.size());
        Polynomial p(size_max);
        
        for (size_t i = 0; i < size_min; ++i) {
            p._coefficients[i] += _coefficients[i] + obj._coefficients[i];
        }
        for (size_t = size_min; i < size_max; ++i) {
            p._coefficients[i] += (size_max == _coefficients.size() ? _coefficients[i] : obj._coefficients[i]);
        }
        return p
    }
```
Same applied to 
```
Polynomial operator- ()
```

```
Polynomial operator*
``` 
can be written like

```
Polynomial operator* (T number) {
    Polynomial p(_coefficients);
    for (auto &_x : p) {
        _x *= number;
     }
    return p;
}
```
Same applied to 
```
Polynomial operator/
```

## "RegularPolygon.h"

Constructor should be inherited from ```Polygon``` or am I stupid

## "Trapezoid.h"

Bad constructor

In ```bool IsValid()``` the life would be mush easier, if the were ```Point& operator-(const Point& other)```
