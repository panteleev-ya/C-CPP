# Code Review (by Anuiel)
## Overall remarks
1. private members should be with underscore like ```_point```


## File BrokenLine.h

No
```
explicit BrokenLine(vector<Point<T>> points) {
    this->points = points;
}
BrokenLine(const BrokenLine& obj) {
    this->points = obj.points;
}
```
Yes
```
explicit BrokenLine(vector<Point<T>> points) points(points) {}
BrokenLine(const BrokenLine& obj) point(obj.point) {}
```


Type T as a return is questionable 
```
T perimeter() {
    T result = static_cast<T>(0);
    for (size_t i = 1; i < points.size(); i++) {
        result += pointsDistance(points[i], points[i - 1]);
    }
    return result;
}
```


## File Point.h

Not
```
explicit Point(T x, T y) {
    this->x = x;
    this->y = y;
}
Point(Point const &obj) {
    this->x = obj.x;
    this->y = obj.y;
}
```

but rather

```    
explicit Point(T x, T y) x(x), y(y) {}

Point(Point const &obj) x(obj.x), y(obj.y) {}
```

Type T as a return is questionable 
```
T pointsDistance(Point<T> p1, Point<T> p2) {
    T xLen = p2.getX() - p1.getX();
    T yLen = p2.getY() - p1.getY();
    return sqrt(static_cast<double>(xLen * xLen + yLen * yLen));
}
```

## File Polygin.h

Not
```
explicit Polygon(vector<Point<T>> points) {
    this->points = points;
}
```
But the
```
explicit Polygon(vector<Point<T>> points) point(point) {}
```

Returning type is questionable
```
virtual T perimeter() {
    T result = static_cast<T>(0);
    for (size_t i = 1; i < points.size(); i++) {
        result += pointsDistance(points[i], points[i - 1]);
    }
    result += pointsDistance(points[points.size() - 1], points[0]);
    return result;
}
```

In ```area()```
```
sum += (x1 + x2) * (y2 - y1);
```
May be overflow

And area of polygon with integer point are integer or [half-integer](https://en.wikipedia.org/wiki/Half-integer), so double usage is questionable here too (from my point of view)

## File Polynomail.h

All returning types should be ```Polynomial& ```, not ```Polynomial```

Bad
```
explicit Polynomial(vector<T> coefficients) {
    this->coefficients = coefficients;
}
```

Good
```
explicit Polynomial(vector<T> coefficients) coefficients(coefficients) {}
```

```
Polynomial operator++ ()
```
can looks like this

```
Polynomial operator++ () {
    for (auto &element : coefficients) {
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
    Polynomial(size_t size) : coefficients(vector<T>(size, 0)) {}
    
public:
    Polynomial operator+ (const Polynomial &obj) {
        size_t size_min = std::min(coefficients.size(), obj.coefficients.size());
        size_t size_max = std::max(coefficients.size(), obj.coefficients.size());
        Polynomial p(size_max);
        
        for (size_t i = 0; i < size_min; ++i) {
            p.coefficients[i] += coefficients[i] + obj.coefficients[i];
        }
        for (size_t = size_min; i < size_max; ++i) {
            p.coefficients[i] += (size_max == coefficients.size() ? coefficients[i] : obj.coefficients[i]);
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
    Polynomial p(coefficients);
    for (auto &x : p) {
        x *= number;
     }
    return p;
}
```
Same applied to 
```
Polynomial operator/
```

## File RegularPolygon.h

Constructor should be inherited from ```Polygon``` or am I stupid

## File Trapezoid.h

Bad constructor

In ```bool IsValid()``` the life would be mush easier, if the were ```Point& operator-(const Point& other)```
