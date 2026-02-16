#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>

class Monom {
private:
    double coef;
    int px;
    int py;
    int pz;

public:
    Monom();
    Monom(double c, int x = 0, int y = 0, int z = 0);
    Monom(const Monom& other);

    Monom& operator=(const Monom& other);

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    bool operator<(const Monom& other) const;

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;
    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;

    Monom operator*(double k) const;
    Monom operator/(double k) const;

    Monom operator-() const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);

    Monom& operator*=(double k);
    Monom& operator/=(double k);

    double Calculate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Monom& m);
    friend std::istream& operator>>(std::istream& is, Monom& m);
};
