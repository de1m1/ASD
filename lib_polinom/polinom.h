#pragma once
#include <iostream>
#include "monom.h"
#include "list.h"

class Polynom {

private:
    List<Monom> monoms;

    void normalize();

public:
    Polynom();
    Polynom(const Monom& m);
    Polynom(const Polynom& other);
    Polynom(const char* str) : Polynom(std::string(str)) {}
    Polynom(const std::string& str);

    Polynom& operator=(const Polynom& other);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);

    double Calculate(double x, double y, double z) const;

    void addMonom(const Monom& m);

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
};