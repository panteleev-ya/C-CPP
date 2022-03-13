#ifndef CLION_POLYNOMIAL_H
#define CLION_POLYNOMIAL_H

#include <type_traits>
#include <vector>
#include <ostream>

using std::vector;

template<typename T>
constexpr bool isNumeric = std::is_same<T, int>::value
                           || std::is_same<T, double>::value
                           || std::is_same<T, long>::value
                           || std::is_same<T, long long>::value
                           || std::is_same<T, short>::value;

template <class T, class=std::enable_if_t<isNumeric<T>>>
class Polynomial {
public:
    Polynomial() = default;
    explicit Polynomial(vector<T> coefficients) {
        this->coefficients = coefficients;
    }
    ~Polynomial() {
        std::destroy(this->coefficients.begin(), this->coefficients.end());
    }

    Polynomial& operator= (const Polynomial& obj) {
        this->coefficients = obj.coefficients;
        return *this;
    }
    Polynomial operator++ () {
        for (size_t i = 0; i < this->coefficients.size(); i++) {
            this->coefficients[i] += 1;
        }
        return *this;
    }
    Polynomial operator-- () {
        for (size_t i = 0; i < this->coefficients.size(); i++) {
            this->coefficients[i] -= 1;
        }
        return *this;
    }
    Polynomial operator+ (const Polynomial &obj) {
        Polynomial p(this->coefficients);

        size_t size = std::min(p.coefficients.size(), obj.coefficients.size());
        size_t i = 0;
        for (; i < size; i++) {
            p.coefficients[i] += obj.coefficients[i];
        }
        while (i < obj.coefficients.size()) {
            p.coefficients.push_back(obj.coefficients[i]);
            i++;
        }
        return p;
    }
    Polynomial operator- (const Polynomial &obj) {
        Polynomial p(this->coefficients);

        size_t size = std::min(p.coefficients.size(), obj.coefficients.size());
        size_t i = 0;
        for (; i < size; i++) {
            p.coefficients[i] -= obj.coefficients[i];
        }
        while (i < obj.coefficients.size()) {
            p.coefficients.push_back(-obj.coefficients[i]);
            i++;
        }
        return p;
    }
    Polynomial operator+= (const Polynomial &obj) {
        *this = *this + obj;
        return *this;
    }
    Polynomial operator-= (const Polynomial &obj) {
        *this = *this - obj;
        return *this;
    }
    Polynomial operator* (T number) {
        Polynomial p(this->coefficients);
        for (size_t i = 0; i < p.coefficients.size(); i++) {
            p.coefficients[i] *= number;
        }
        return p;
    }
    Polynomial operator/ (T number) {
        Polynomial p(this->coefficients);
        for (size_t i = 0; i < p.coefficients.size(); i++) {
            p.coefficients[i] /= number;
        }
        return p;
    }
    Polynomial operator*= (T number) {
        *this = *this * number;
        return *this;
    }
    Polynomial operator/= (T number) {
        *this = *this / number;
        return *this;
    }
    bool operator== (Polynomial obj) {
        if (this->coefficients.size() != obj.coefficients.size()) {
            return false;
        }
        for (size_t i = 0; i < this->coefficients.size(); i++) {
            if (this->coefficients[i] != obj.coefficients[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!= (const Polynomial &obj) {
        return !(*this == obj);
    }
    std::ostream& operator<< (std::ostream &out) {
        for (T c : this->coefficients) {
            out << c << ' ';
        }
        return out;
    }
    std::ostream& operator>> (std::ostream &in) {
        for (size_t i = 0; i < this->coefficients.size(); i++) {
            in >> this->coefficients[i];
        }
        return in;
    }
    T operator[] (size_t index) {
        if (this->coefficients.size() == 0) {
            return static_cast<T>(0);
        }
        return this->coefficients[index % this->coefficients.size()];
    }
private:
    vector<T> coefficients;
};


#endif //CLION_POLYNOMIAL_H
