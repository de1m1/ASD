#include "monom.h"
#include <cmath>
#include <stdexcept>



Monom::Monom() : coef(0), px(0), py(0), pz(0) {}

Monom::Monom(double c, int x, int y, int z): coef(c), px(x), py(y), pz(z){
    if (coef == 0) px = py = pz = 0;
}

Monom::Monom(const Monom& other): coef(other.coef), px(other.px), py(other.py), pz(other.pz) {}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        coef = other.coef;
        px = other.px;
        py = other.py;
        pz = other.pz;
    }
    return *this;
}

bool Monom::operator==(const Monom& other) const {
    return px == other.px && py == other.py && pz == other.pz;
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

bool Monom::operator<(const Monom& other) const {
    if (px != other.px) return px > other.px;
    if (py != other.py) return py > other.py;
    return pz > other.pz;
}

Monom Monom::operator+(const Monom& other) const {
    if (!(*this == other)) throw std::logic_error("Different monoms!");
    return Monom(coef + other.coef, px, py, pz);
}

Monom Monom::operator-(const Monom& other) const {
    if (!(*this == other)) throw std::logic_error("Different monoms!");
    return Monom(coef - other.coef, px, py, pz);
}

Monom Monom::operator*(const Monom& other) const {
    return Monom(coef * other.coef,
        px + other.px,
        py + other.py,
        pz + other.pz);
}

Monom Monom::operator/(const Monom& other) const {
    if (other.coef == 0)
        throw std::logic_error("Division by zero!");

    return Monom(coef / other.coef,
        px - other.px,
        py - other.py,
        pz - other.pz);
}

Monom Monom::operator*(double k) const {
    return Monom(coef * k, px, py, pz);
}

Monom Monom::operator/(double k) const {
    if (k == 0) throw std::logic_error("Division by zero!");
    return Monom(coef / k, px, py, pz);
}

Monom Monom::operator-() const {
    return Monom(-coef, px, py, pz);
}

Monom& Monom::operator+=(const Monom& other) {
    *this = *this + other;
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    *this = *this - other;
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    *this = *this * other;
    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    *this = *this / other;
    return *this;
}

Monom& Monom::operator*=(double k) {
    *this = *this * k;
    return *this;
}

Monom& Monom::operator/=(double k) {
    *this = *this / k;
    return *this;
}

double Monom::Calculate(double x, double y, double z) const {
    return coef * std::pow(x, px)
        * std::pow(y, py)
        * std::pow(z, pz);
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    if (m.coef == 0) return os << "0";

    if (m.coef != 1 || (m.px == 0 && m.py == 0 && m.pz == 0)) os << m.coef;

    if (m.px) os << "x^" << m.px;
    if (m.py) os << "y^" << m.py;
    if (m.pz) os << "z^" << m.pz;

    return os;
}

std::istream& operator>>(std::istream& is, Monom& m) {
    is >> m.coef >> m.px >> m.py >> m.pz; return is;
}
