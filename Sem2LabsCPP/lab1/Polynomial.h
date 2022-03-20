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
    explicit Polynomial(vector<T> coefficients) : _coefficients(coefficients) {

    }
    ~Polynomial() {
        std::destroy(this->_coefficients.begin(), this->_coefficients.end());
    }

    Polynomial& operator= (const Polynomial& obj) {
        this->_coefficients = obj._coefficients;
        return *this;
    }
    Polynomial& operator++ () {
        for (auto& c: _coefficients) {
            c++;
        }
        return *this;
    }
    Polynomial& operator-- () {
        for (auto& c: _coefficients) {
            c--;
        }
        return *this;
    }
    Polynomial operator+ (const Polynomial &obj) const {
        Polynomial p(this->_coefficients);

        size_t min_size = std::min(_coefficients.size(), obj.coefficients.size());
        size_t obj_size = obj.coefficients.size();
        for (size_t i = 0; i < min_size; i++) {
            p._coefficients[i] += obj._coefficients[i];
        }
        for (size_t i = min_size; i < obj_size; i++) {
            p._coefficients.push_back(obj._coefficients[i]);
        }
        return p;
    }
    Polynomial operator- (const Polynomial &obj) const {
        Polynomial p(this->_coefficients);

        size_t min_size = std::min(_coefficients.size(), obj.coefficients.size());
        size_t obj_size = obj.coefficients.size();
        for (size_t i = 0; i < min_size; i++) {
            p._coefficients[i] -= obj._coefficients[i];
        }
        for (size_t i = min_size; i < obj_size; i++) {
            p._coefficients.push_back(-obj._coefficients[i]);
        }
        return p;
    }
    Polynomial& operator+= (const Polynomial &obj) {
        *this = *this + obj;
        return *this;
    }
    Polynomial& operator-= (const Polynomial &obj) {
        *this = *this - obj;
        return *this;
    }
    Polynomial operator* (T number) const {
        Polynomial p(this->_coefficients);
        for (auto& c: _coefficients) {
            c *= number;
        }
        return p;
    }
    Polynomial operator/ (T number) const {
        Polynomial p(this->_coefficients);
        for (auto& c: _coefficients) {
            c /= number;
        }
        return p;
    }
    Polynomial& operator*= (T number) const {
        *this = *this * number;
        return *this;
    }
    Polynomial& operator/= (T number) const {
        *this = *this / number;
        return *this;
    }
    bool operator== (Polynomial obj) const {
        if (this->_coefficients.size() != obj._coefficients.size()) {
            return false;
        }
        for (size_t i = 0; i < this->_coefficients.size(); i++) {
            if (this->_coefficients[i] != obj._coefficients[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!= (const Polynomial &obj) const {
        return !(*this == obj);
    }
    std::ostream& operator<< (std::ostream &out) const {
        for (T c : this->_coefficients) {
            out << c << ' ';
        }
        return out;
    }
    std::ostream& operator>> (std::ostream &in) const {
        for (size_t i = 0; i < this->_coefficients.size(); i++) {
            in >> this->_coefficients[i];
        }
        return in;
    }
    T operator[] (size_t index) const {
        if (this->_coefficients.size() == 0) {
            return static_cast<T>(0);
        }
        return this->_coefficients[index % this->_coefficients.size()];
    }
private:
    vector<T> _coefficients;
};


#endif //CLION_POLYNOMIAL_H
