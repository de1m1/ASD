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

    for (size_t i = 0; i < monoms.size(); ++i)
        if (!(monoms[i] == other.monoms[i]))
            return false;

    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

void Polynom::normalize() {

    if (monoms.size() == 0)
        return;

    for (size_t i = 0; i < monoms.size(); ++i)
        for (size_t j = i + 1; j < monoms.size(); ++j)
            if (monoms[j] < monoms[i]) {
                Monom temp = monoms[i];
                monoms[i] = monoms[j];
                monoms[j] = temp;
            }

    for (size_t i = 0; i + 1 < monoms.size();) {

        if (!(monoms[i] < monoms[i + 1]) && !(monoms[i + 1] < monoms[i])) {
            monoms[i] += monoms[i + 1];
            for (size_t j = i + 1; j + 1 < monoms.size(); ++j)
                monoms[j] = monoms[j + 1];
            monoms.pop_back();
        }
        else {
            ++i;
        }
    }

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
    for (size_t i = 0; i < other.monoms.size(); ++i)
        monoms.push_back(other.monoms[i]);

    normalize();
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    for (size_t i = 0; i < other.monoms.size(); ++i)
        monoms.push_back(-other.monoms[i]);

    normalize();
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    Polynom tmp;

    for (size_t i = 0; i < monoms.size(); ++i)
        for (size_t j = 0; j < other.monoms.size(); ++j)
            tmp.monoms.push_back(monoms[i] * other.monoms[j]);

    tmp.normalize();
    monoms = tmp.monoms;
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

    os << p.monoms[0];

    for (size_t i = 1; i < p.monoms.size(); ++i) {

        double val = p.monoms[i].Calculate(1, 1, 1);

        if (val < 0)
            os << " - " << (-p.monoms[i]);
        else
            os << " + " << p.monoms[i];
    }

    return os;
}