#include "polinom.h"

Polynom::Polynom() {}

Polynom::Polynom(const Monom& m) {
    monoms.push_back(m);
    normalize();
}

Polynom::Polynom(const Polynom& other)
    : monoms(other.monoms) {
}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other)
        monoms = other.monoms;
    return *this;
}

bool Polynom::operator==(const Polynom& other) const {

    if (monoms.size() != other.monoms.size())
        return false;

    for (size_t i = 0; i < monoms.size(); ++i) {
        if (!(monoms[i] == other.monoms[i]) ||
            monoms[i].Calculate(1,1,1) != other.monoms[i].Calculate(1,1,1))
            return false;
    }
    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

void Polynom::normalize() {

    if (monoms.size() == 0)
        return;

    // сортировка
    for (size_t i = 0; i < monoms.size(); ++i)
        for (size_t j = i + 1; j < monoms.size(); ++j)
            if (monoms[j] < monoms[i]) {
                Monom tmp = monoms[i];
                monoms[i] = monoms[j];
                monoms[j] = tmp;
            }

    // объединение одинаковых степеней
    for (size_t i = 0; i + 1 < monoms.size();) {

        if (!(monoms[i] < monoms[i + 1]) &&
            !(monoms[i + 1] < monoms[i])) {

            monoms[i] += monoms[i + 1];

            for (size_t j = i + 1; j + 1 < monoms.size(); ++j)
                monoms[j] = monoms[j + 1];

            monoms.pop_back();
        }
        else {
            ++i;
        }
    }

    // удаление нулевых
    for (size_t i = 0; i < monoms.size();) {
        if (monoms[i] == Monom()) {
            for (size_t j = i; j + 1 < monoms.size(); ++j)
                monoms[j] = monoms[j + 1];

            monoms.pop_back();
        }
        else {
            ++i;
        }
    }
}

void Polynom::addMonom(const Monom& m) {
    monoms.push_back(m);
    normalize();
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result = *this;
    for (size_t i = 0; i < other.monoms.size(); ++i)
        result.monoms.push_back(other.monoms[i]);

    result.normalize();
    return result;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result = *this;
    for (size_t i = 0; i < other.monoms.size(); ++i)
        result.monoms.push_back(-other.monoms[i]);

    result.normalize();
    return result;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom result;

    for (size_t i = 0; i < monoms.size(); ++i)
        for (size_t j = 0; j < other.monoms.size(); ++j)
            result.monoms.push_back(monoms[i] * other.monoms[j]);

    result.normalize();
    return result;
}

Polynom& Polynom::operator+=(const Polynom& other) {
    *this = *this + other;
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    *this = *this - other;
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;
    return *this;
}

double Polynom::Calculate(double x, double y, double z) const {
    double sum = 0;
    for (size_t i = 0; i < monoms.size(); ++i)
        sum += monoms[i].Calculate(x, y, z);
    return sum;
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {

    if (p.monoms.size() == 0) {
        os << 0;
        return os;
    }

    for (size_t i = 0; i < p.monoms.size(); ++i) {
        if (i > 0)
            os << " + ";
        os << p.monoms[i];
    }

    return os;
}